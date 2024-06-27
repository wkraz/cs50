'''
-- flat-file database: code for a text containing all your data - .txt, .csv (comma separated values)
-- reading csv files in python:
--      import csv
--      with open("favorites.cvs", "r") as file:
--          reader = csv.DictReader(file)
--          for row in reader:
--              print(row[1]) # prints the second column of every row
-- to count and sort csv data in python:
-- import csv
-- from collections import Counter
-- with open("favorites.csv", "r") as file:
--      reader = csv.DictReader(file)
--      counts = Counter()
--      for row in reader:
--          favorite = row["favorite"]
--          counts[favorite] += 1
-- for favorite, count in counts.most_common():
--      print(f"{favorite}: {counts[favorite]}")
--
-- sql: structured query language
--      typically you don't write loops -- you tell the database what you are looking for
--      lets us do what python does but in way less lines
-- follows CRUD: create (insert), read, update, delete (drop) are the only four things you can do in a database
-- we will be using sqlite3
-- sqlite3 favorites.db => loads you into the favorites database
--      .mode csv => puts you into csv mode
--      .import favorites.csv favorites (table name)
--      .quit
-- favorites.db is basically now an optimized version of favorites.csv
--      .scehma => shows schema of database
--      SELECT * FROM favorites; => select EVERYTHING from favorites database
--      SELECT language FROM favorites LIMIT 10; => just langauge column, and only 10 rows
--      SELECT DISTINCT(language) from favorites; => outputs all 3 types of languages
--      SELECT COUNT(*) FROM favorites WHERE language = 'C'; => shows how many instances of C language there are
--      SELECT language, COUNT(*) FROM favorites GROUP BY language ORDER BY COUNT(*) DESC; => shows how many instances of each language there are, highest->lowest
--      INSERT INTO favorites (language, problem) VALUES('sql', 'fiftyville'); => adding a new value into the table w/ value sql: fiftyville
--      DELETE FROM favorites WHERE Timestamp IS NULL; => deleting all values w/out timestamp from table
querying: getting information from the database by asking questions
how to join together two tables that have information you care about around the common id number (metadata):
    sqlite3 shows.db
    SELECT * from shows JOIN ratings ON shows.id = ratings.show_id WHERE rating >= 6.0 LIMIT 10;
    -- now, we only care about title and rating so run:
    SELECT title, rating from shows ___ same as command above
looking at specific value in table:
    SELECT * FROM shows WHERE id = 63881;
    -- can also do ...WHERE id IN (some other table) instead of id = ___
        -- this is nesting queries, and you can keep doing it over and over again
    alternative way:
    SELECT title FROM shows, stars, people WHERE shows.id = stars.shows_id AND people.id = stars.person_id AND name = 'Steve Carell';
        shows us shows that Steve Carell has starred in
indexes: data structure that makes it faster to perform queries - computer loads in the column once and it loads instantly afterwards
    CREATE INDEX title_index ON shows (title); -- index the shows column, because I'll be using it a lot in the future
    specifically, it's building a b-tree (not binary)
    primary keys are indexed by default
% works as a wildcard character - LIKE "Harry Potter%" is anything starting w/ Harry Potter

'''

# can run sql in python
from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite)
row = rows[0]
