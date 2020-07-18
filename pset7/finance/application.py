from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Select data from buy
    user_data = db.execute("SELECT * FROM buy WHERE id = :id", id=session["user_id"])
    user_cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

    total_cash = 0

    # Update database
    for item in user_data:
        stock = lookup(item["symbol"])
        price = stock["price"]
        stock_symbol = item["symbol"]
        shares = item["shares"]
        stock_value = price * shares
        total_cash += stock_value
        db.execute("UPDATE buy SET price = :price, total = :total WHERE id = :id AND symbol = :symbol",
                   price=usd(price), total=usd(stock_value), id=session["user_id"], symbol=stock_symbol)

    # Calculate the amount of cash user has in total
    total_cash += user_cash[0]["cash"]

    # Extract data
    updated_data = db.execute("SELECT * FROM buy WHERE id = :id", id=session["user_id"])
    cash = usd(user_cash[0]["cash"])

    return render_template("index.html", stock=updated_data, cash=cash, total_cash=usd(total_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Prompt user for symbol
    if request.method == "GET":
        return render_template("buy.html")

    else:

        # Check if symbol field is empty
        if not request.form.get("symbol"):
            return apology("Symbol can not be blank!")

        # Check if symbol is valid
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol is not valid!")

        if not request.form.get("shares").isdigit():
            return apology("Invalid number.")
        elif float(request.form.get("shares")).is_integer():
            # Check if shares field is empty
            if not request.form.get("shares"):
                return apology("Please enter number of shares")
            elif int(request.form.get("shares")) <= 0:
                return apology("Invalid number.")
        else:
            return apology("Number must be an integer.")

        # How much does the user buy
        shares = int(request.form.get("shares"))
        price = float(stock["price"])
        total = float(price * shares)

        # How much does the user currently have
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # How much does the user have after the buying
        if not cash or float(cash[0]["cash"]) < total:
            return apology("Sorry, you don't have enough money :(")

        # Update user cash
        db.execute("UPDATE users SET cash = cash - :total WHERE id = :id",
                   id=session["user_id"], total=total)

        # Write in history
        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)",
                   id=session["user_id"], symbol=stock["symbol"], shares=shares, price=usd(stock["price"]))

        # Check if user already bought the stock
        user_buy = db.execute("SELECT shares FROM buy WHERE symbol = :symbol AND id = :id",
                              symbol=stock["symbol"], id=session["user_id"])
        # If user has the stock, update shares
        if user_buy:
            total_shares = int(user_buy[0]["shares"]) + shares
            db.execute("UPDATE buy SET shares=:shares WHERE id = :id AND symbol = :symbol",
                       shares=total_shares, id=session["user_id"], symbol=stock["symbol"])

        # If user doesn't have the stock, add new stock
        else:
            new_buy = db.execute("INSERT INTO buy (symbol, name, shares, price, total, id) VALUES (:symbol, :name, :shares, :price, :total, :id)",
                                 symbol=stock["symbol"], name=stock["name"], shares=shares, price=usd(stock["price"]), total=usd(total), id=session["user_id"])

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE id = :id", id=session["user_id"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

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

    # Prompt user for symbol
    if request.method == "GET":
        return render_template("quote.html")
    # Search for the symbol
    else:
        # Check if symbol is entered
        if not request.form.get("symbol"):
            return apology("symbol is required!")
        # Check if the symbol is valid
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("symbol is not valid!")
        else:
            return render_template("quoted.html", quote=quote, price=usd(quote["price"]))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was entered
        if not request.form.get("username"):
            return apology("please enter username")

        # Ensure password was entered
        elif not request.form.get("password"):
            return apology("please enter password")

        # Ensure password was confirmed
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("passwords don't match")

        elif request.form.get("password"):
            password = request.form.get("password")
            upletter_count = 0
            lowletter_count = 0
            digit_count = 0
            symbol_count = 0

            if len(password) < 8:
                flash("Your password must contain at least 8 characters!")
                return render_template("register.html")

            for char in password:
                if char.isupper():
                    upletter_count += 1
                if char.islower():
                    lowletter_count += 1
                if char.isdigit():
                    digit_count += 1

            if upletter_count < 1:
                flash("Please enter at least ONE upper case letter")
                return render_template("register.html")

            elif lowletter_count < 1:
                flash("Please enter at least ONE lower case letter")
                return render_template("register.html")

            elif digit_count < 1:
                flash("Please enter at least ONE digit")
                return render_template("register.html")

        # Insert username and password into database and ensure the username not already exists
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))
        if not result:
            return apology("Opps! This username has been taken!")
        else:
            flash("Thank you for registering!")
            return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        symbols = db.execute("SELECT * FROM buy WHERE id = :id", id=session["user_id"])
        return render_template("sell.html", symbols=symbols)
    else:
        stock = lookup(request.form.get("symbol"))
        sell_shares = int(request.form.get("shares"))
        user_data = db.execute("SELECT shares FROM buy WHERE id = :id AND symbol = :symbol",
                               id=session["user_id"], symbol=stock["symbol"])
        old_shares = int(user_data[0]["shares"])

        # Check if symbol is entered
        if not request.form.get("symbol"):
            return apology("Symbol is required!")

        # If user doesn't have any shares of the stock
        elif not old_shares:
            return apology("Sorry, you don't have any shares of this stock")

        # Check if number of shares is entered
        elif not sell_shares:
            return apology("Please enter how many shares you want to sell.")

        # If user does't have that many shares of the stock
        elif sell_shares > old_shares:
            return apology("Sorry, looks like you don't have that many shares. :(")

        # Write in history
        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)",
                   id=session["user_id"], symbol=stock["symbol"], shares=-sell_shares, price=usd(stock["price"]))
        db.execute("UPDATE users SET cash = cash + :sell WHERE id = :id",
                   sell=sell_shares * stock["price"], id=session["user_id"])

        total_shares = old_shares - sell_shares
        if total_shares == 0:
            db.execute("DELETE FROM buy WHERE id = :id AND symbol = :symbol",
                       id=session["user_id"], symbol=stock["symbol"])

        else:
            db.execute("UPDATE buy SET shares = shares - :shares, total = total - :sell WHERE id = :id AND symbol = :symbol",
                       shares=sell_shares, sell=sell_shares * stock["price"], id=session["user_id"], symbol=stock["symbol"])

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
