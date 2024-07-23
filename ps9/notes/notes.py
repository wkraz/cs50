"""
LECTURE 09 NOTES
FLASK
----------------

micro web framework that lets you use Python to write backend of web applications

how to get input (name):
    name = request.args["name"]
    # you put this "input" in the search bar:
    _____.google.com/?name=Will
    # can also use:
    name = request.args.get("name", None)
    # .get is a dictionary function

how to return a template of another html file:
    return render_template("index.html", placeholder=name)
    # here, in index.html there is a variable called placeholder whose value you're assigning to the name variable above
    # {{ placeholder }} is how you use a placeholder in an html file

Jinja - templating engine
"layout.html"
<body>
    {% block body}{% endblock %}
</body>
this becomes a placeholder for an entire block of code now

Then to reference this template in "greet.html":
{% extends "layout.html" %} # example of inheritance

{% block body %}

    hello, {{ name }}

{% endblock %}
Basically, it copies everything from layout.html except the line: hello, {{ name }}
An easy way to make a new file that has the same layout as others, but with slight changes

You can use the http method: post to get information and store it; more secure than get
How to check method type:
    if request.method == "POST": (can replace with get, etc)

<select> is a dropdown menu in HTML
    <option> is each choice
</select>
So is <radio> which is side by side buttons with choices
Also <checkbox>

You can do for loops in jinja
to loop through an array: sports = ["basketball", "soccer", "football"]
{% for sport in sports %}
    <option>{{ sport }}</option>
{% endfor %}

Jinja if else block to check if a user is logged in
{% if name %}
    You are logged in as {{ name }}.
{% else %}
    You are not logged in.
{% endif %}

fetch - JS command that lets you pass information to the URL that you want to get

API - application programming interface
    standardized way of getting data from someone else's server into your application

JSON - javascript object notation
looks similar to python dictionary syntax
jsonify() function converts output to json file

"""

# How to import
from flask import Flask, redirect, render_template, request, session # you import session if you want to work with cookies
from flask_session import Session

app = Flask(__name__)

app.config["SESSION_PERMANENT"] = False # ensures cookie is deleted when you leave the browser (session is not permanent)
app.config["SESSION_TYPE"] = "filesystem" # makes sure data is stored in server's files, not in the cookies themselves
Session(app) # starts the session on the app

@app.route("/", methods=["POST"]) # / is the default route to implement Flask, post method is what we want
def index():
    return render_template("index.html", name=session.get("name"))
# Whenever someone reaches "/", the index function gets called


@app.route("/login")
def login():
    if request.method() == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("login.html") # pretend login.html exists and is a form for logging in

@app.route("/logout")
def logout():
    session.clear() # clear the contents of the session
    return redirect("/") # back to homepage

"""
login.html

<form action="/login" method="post">
    <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
    <button type="submit">Log in</button>
</form>

"""

# how to actually run it
if __name__ == "__main__":
    app.run()

