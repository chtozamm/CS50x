import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, time_now

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
# if not os.environ.get("API_KEY"):
# raise RuntimeError("API_KEY not set")


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
    # TODO: add coments
    user_id = session.get("user_id")
    owns = own_shares(user_id)
    total = 0
    """
    DONE:
    1. figure out how the loop below works
    2. figure out the problem that appears without try/except
    """
    for symbol, shares in owns.items():
        result = lookup(symbol)
        name, price = result["name"], result["price"]
        stock_value = shares * price
        total += stock_value
        owns[symbol] = (name, shares, usd(price), usd(stock_value))
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    total += cash
    return render_template("index.html", owns=owns, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Get and validate symbol
        result = lookup(request.form.get("symbol").strip())
        if not result:
            return apology("Invalid symbol")

        # Get and validate amount of shares
        shares = int(request.form.get("shares"))
        if not shares:
            return apology("Invalid amount of shares")

        if shares < 1:
            return apology("Amount of shares must be positive")

        # Set variables needed for query
        user_id = session.get("user_id")
        symbol = result["symbol"]
        price = result["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        remain = cash - price * shares
        if remain < 0:
            return apology("Not enough cash to buy shares")

        # Update user's cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, user_id)

        # Store order in database
        db.execute("INSERT INTO orders (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)", user_id, symbol, shares, price, time_now())

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol, shares, price, timestamp FROM orders WHERE user_id = ?", session.get("user_id"))
    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Invalid stock symbol", 403)
        share = lookup(symbol)
        if not share:
            return apology("Couldn't1 find price", 403)
        return render_template("quoted.html", share=share)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Invalid username", 403)

        # Check if username already exists
        username_found = db.execute(
            "SELECT username FROM users WHERE username = ?", username)
        if username_found:
            return apology("Username already exists", 403)

        password = request.form.get("password")
        password_confirmation = request.form.get("password_confirmation")

        if not password or not password_confirmation:
            return apology("Invalid password", 403)

        if password_confirmation != password:
            return apology("Passwords do not match", 403)

        password_hash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, password_hash)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """
    TODO:
    1. Show on sell.html amount of owned shares
    """
    """Sell shares of stock"""
    user_id = session.get("user_id")
    owns = own_shares(user_id)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if owns[symbol] < shares:
            return render_template("sell.html", invalid=True, symbol=symbol, owns=owns.keys())
        result = lookup(symbol)
        price = result["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        gain = price * shares
        cash += gain
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)
        db.execute("INSERT INTO orders (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)", user_id, symbol, -shares, price, time_now())
        return redirect("/")
    else:
        return render_template("sell.html", owns=owns.keys())

# TODO: move function to helpers.py
def own_shares(user_id):
    owns = {}
    query = db.execute("SELECT symbol, shares FROM orders WHERE user_id = ?", user_id)
    for q in query:
        symbol, shares = q["symbol"], q["shares"]
        owns[symbol] = owns.setdefault(symbol, 0) + shares

    # TODO: figure out the line:
    # filter zero-share stocks
    # owns = {k: v for k, v in owns.items() if v != 0}
    return owns