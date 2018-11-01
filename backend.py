from flask import Flask, render_template, redirect, url_for, request, g
import sqlite3

app = Flask(__name__)


def check_password(hashed_password, user_password):
    return hashed_password == user_password


def validate(username, password):
    con = sqlite3.connect('static/user.db')
    completion = False
    with con:
        cur = con.cursor()
        cur.execute("SELECT * FROM Users")
        rows = cur.fetchall()
        for row in rows:
            dbUser = row[0]
            dbPass = row[1]
            if dbUser == username:
                completion = check_password(dbPass, password)
    return completion


@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        completion = validate(username, password)
        if not completion:
            error = 'Invalid Credentials. Please try again.'
        else:
            return redirect(url_for('success'))
    return render_template('login.html', error=error)


@app.route('/success')
def success():
    return "You have successfully logged in"


if __name__ == '__main__':
    app.run()
