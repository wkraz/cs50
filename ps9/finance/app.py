import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get a list of all transactions
    transactions = db.execute("SELECT * FROM transactions WHERE id = ?", session["user_id"])
    # get current cash balance
    current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    return render_template("index.html", transactions=transactions, current_cash=current_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # get data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # make sure shares is an integer
        if not shares.isdigit():
            return apology("invalid shares", 400)
        shares = int(shares)
        # validate
        # ensure symbol submitted
        if not symbol:
            return apology("invalid symbol", 400)

        # use API to look up symbol
        response = lookup(symbol)
        # check if symbol is valid
        if response is None:
            return apology("invalid symbol", 400)
        # check if shares is a positive integer
        if not shares > 0:
            return apology("shares must be positive", 400)

        # see how much it costs
        buy_price = response["price"] * shares

        # see how much money the user has and subtract this from it (if possible)
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if balance[0]['cash'] < buy_price:  # you're broke lmao
            return apology("insufficient funds", 400)
        else:
            cash = balance[0]["cash"]

            new_balance = cash - buy_price

            # add transaction to transaction table to keep track
            db.execute("INSERT INTO transactions(id, shares, symbol, time, price, cash, type, value) values(?, ?, ?, CURRENT_TIMESTAMP, ?, ?, ?, ?)",
                       session["user_id"], shares, symbol, response["price"], new_balance, "buy", buy_price)

            # update users table with new cash balance
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

            # tell the user it's bought
            flash("Bought!")

            # go to home page
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # get a list of all transactions
    transactions = db.execute(
        "SELECT id, symbol, shares, price, time FROM transactions WHERE id = ? ORDER BY time", session["user_id"])

    # link history.html
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # get stock symbol
    if request.method == "POST":  # form submitted
        # get symbol
        symbol = request.form.get("symbol")
        # ensure symbol submitted
        if not symbol:
            return apology("invalid symbol", 400)

        # use API to look up symbol
        response = lookup(symbol)
        # check if symbol is valid
        if response is None:
            return apology("invalid symbol", 400)
        else:
            return render_template("quoted.html", symbol=response["symbol"], price=response["price"])

    else:  # clicked on, so take them to quote.html
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":  # they submitted the form
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # ensure username submitted
        if not username:
            return apology("empty username", 400)
        if not password:
            return apology("empty password", 400)
        if not confirmation:
            return apology("empty confirmation password", 400)
        # query for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        # if rows != 0, user is in database
        if len(rows) != 0:
            return apology("username already exists", 400)
        # now the username is valid

        # see if the passwords match
        if password != confirmation:
            return apology("passwords do not match", 400)
        else:
            # hash password to store it
            hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

            # now that everything is validated, add it to database
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, hash)

            # no errors have happened, so return to main page
            return redirect("/login")

    else:  # they clicked on the link to open the page
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # get data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # validate
        if not shares.isdigit():
            return apology("invalid shares", 403)
        shares = int(shares)
        if not shares > 0:
            return apology("shares must be positive", 403)

        # see how many shares of this stock have been bought and sold
        # make sure bought - sold - num about to sell > 0
        num_bought = 0
        num_sold = 0
        shares_bought = db.execute(
            "SELECT shares FROM transactions WHERE id = ? AND type = ? AND symbol = ?", session["user_id"], "buy", symbol)
        if len(shares_bought) != 0:
            num_bought = shares_bought[0]["shares"]
        shares_sold = db.execute(
            "SELECT shares FROM transactions WHERE id = ? AND type = ? AND symbol = ?", session["user_id"], "sell", symbol)
        if len(shares_sold) != 0:
            num_sold = shares_sold[0]["shares"]
        if num_bought - num_sold - shares <= 0:
            return apology("no shares left to sell", 403)
        else:
            shares_left = num_bought - num_sold - shares
            response = lookup(symbol)
            # get latest cash balance and update it
            transactions = db.execute("SELECT * FROM transactions WHERE id = ?", session["user_id"])
            if len(transactions) == 0:
                return apology("no transactions yet", 403)
            current_cash = transactions[len(transactions) - 1]["cash"]
            new_balance = current_cash + (shares * response["price"])

            # add successful sell into transactions
            db.execute("INSERT INTO transactions(id, shares, symbol, time, price, cash, type, value) values(?, ?, ?, CURRENT_TIMESTAMP, ?, ?, ?, ?)",
                       session["user_id"], shares, symbol, response["price"], new_balance, "sell", shares * response["price"])

            # go to sold page and inform them of the transaction
            return render_template("sold.html", shares=shares, symbol=symbol)

    else:
        # see which stocks the user has purchased
        stocks = db.execute("SELECT symbol FROM transactions WHERE id = ?", session["user_id"])
        symbols = []
        for stock in stocks:
            symbols.append(stock["symbol"])
        return render_template("sell.html", symbols=symbols)


@app.route("/newpassword", methods=["GET", "POST"])
@login_required
def newpassword():
    if request.method == "POST":
        # get data
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # validate
        if not username:
            return apology("invalid username", 403)
        # see if the passwords match
        if password != confirmation:
            return apology("passwords do not match", 403)
        else:
            # hash password to store it
            password = generate_password_hash(password)

            # now change password to new password
            db.execute("UPDATE users SET hash = ? WHERE id = ?", password, session["user_id"])

            # no errors have happened, so return to login
            return redirect("/login")
    else:
        return render_template("newpassword.html")
