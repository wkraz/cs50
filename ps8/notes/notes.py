'''
NOTES
------------------------------

-------HTML------------------
tags & attributes
    tags are like body, head, p, etc
    attributes are like html LANG="EN", and give functionality to tags

cs50 files are in codespace not your computer, so you need to run: http-server
    leads you to a link where you can view the files
can think of html doc as a tree
most basic html page:

<!DOCTYPE html>
<html lang="en">
    <head>
        <title>
            This is the title.
        </title>
    </head>
    <body>
        body
    </body>
</html>
Tags: <p> - paragraph
<h_> - header (_ represents a number: 1 is largest, goes down)
<ul> - unordered list
    <li> - list item => child of <ul>, used for each item
<ol> - ordered list (numbered)
<!-- Comment -->          how to comment in html

how to make a table
<table>
    <tr> - table row
        <td> - table data

<img alt="photo of bridge" src="bridge.png"> - loading image "bridge.png"; if not loaded it shows alt: "photo of bridge" text

Adding video with controls (play, pause, etc)
<video controls>
    <source src="video.mp4" type="video/mp4">

Hyperlinking
Visit <a href="https://www.harvard.edu">Harvard</a>.
    Shows "Harvard" instead of hyperlink

Making websites mobile user friendly
<head>
    <meta name="viewport" content="initial-scale=1, width=device-width">

Making a button
<body>
    <form>
        <input>
        <button>Search</button>
    </form>

Regular expressions: regexes
    Sequence of characters that the computer looks for
    <input pattern=".+@.+\.edu"> - makes it so the only accepted inputs have @ and .edu
    . represents any character
    + represents whatever follows occurs one or more times

-----------HTML---------------

-----------CSS----------------
controls the style of the website
In HTML, you include a <style> tag and include css in there
OR
<link href="styles.css" rel="stylesheet"> which takes you to styles.css and you add css code there

Don't have to explicitly write css code, can do it as html attributes:
<body>
    <div style="font-size: large; text-align: center">
        Hello.
    </div>
    <div style="font-size: medium">
        Hello, smaller. etc
Better to use <div> instead of <p> a lot of the time -- when you don't need actual paragraphs these make more sense
Divs are just rectangualr regions of the page
On a parent tag, you can do this to apply it to all children:
<body style="text-align: center"> - it "cascades" down to all the children
&#169; is how you type the copyright symbol in HTML (can just look these up)

Can also use:
<body>
    <header></header>
    <main></main>
    <footer></footer>
OR:
<head>
    <style> <!-- can also just outsource this with <link href="styles.css" rel="stylesheet"> -->
        body
        {
            text-align: center;
        }
        header
        {
            font-size: large;
        }
Can also make your own tags:
.center
{
    text-align: center;
}
Then,
<body class="centered"> which simplifies it in the long run

Can do this with a link: Visit <a href="https://www.harvard.edu/">Harvard</a>.
<style>
    a
    {
        color:red;
        text-decoration: none;
    }
    a:hover
    {
        text-decoration: underline; <!-- when you hover over link, underline it -->
    }
Can give unique ids to links:
<a href="harvard.edu" id="harvard">
<a href="yale.edu" id="yale">
Then in <style>,
<style>
    #harvard
    {
        color: red;
    }
    #yale
    {
        color: blue;
    }

-----------CSS-----------------

Frameworks:
Designs that people have created that make pages look prettier
Bootstrap is one of these frameworks
In <head>, you link a frameworks documentation to your html doc:
    <link href="https://bootstrap.css" rel="stylesheet"> and just get their styling for free (cheat code)

------JS-------------
Actual programming language unlike HTML/CSS

Triggered by using <script> tag
ex that writes a function to greet the user with 'hello, (name)':
<head>
    <script>
        function greet()
        {
            alert('hello, ' + document.querySelector('#name').value);
        }
    </script>
concatenates strings w/ + just like Python
object oriented
Whole page is a document, so you can run document.querySelector
Then just run .value to go inside the structure, because it's OOP
ex looking for input:
document.querySelector('form').addEventListener('submit', function(event)) {
    alert('hello, ' + document.querySelector('#name').value);
    event.preventDefault();
}
    - Constantly waits for the event: submit to be triggered, and then calls the function below when it is triggered
    - "anonymous function" because you never give the function a name
    - .preventDefault() keeps you from submitting anything to the server on accident

Way to wait until entire website is loaded before you do anything:
document.addEventListener('DOMContentLoaded', function()) {
    rest of website code
}
- lets computer read all the HTML top to bottom

Declare variables using let var = ____;
How to make 3 RGB buttons that change the color of the background w/ JS:

let body = document.querySelector('body');
document.querySelector('#red').addEventListener('click', function() {
    body.style.backgroundColor = 'red';
)};
same for green and blue
listening for clicks and then triggering functions

How to wait 500 ms:
window.setInterval(blink, 500); where blink is a function defined earlier

How to get people's locations:
navigator.geolocation.getCurrentPosition(function(position) {
    document.write(position.coords.latitude + ", " + position.coords.longitude);
});

------JS-------------

------------------------------
'''
