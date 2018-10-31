from flask import Flask, render_template

app = Flask(__name__, static_url_path='')


@app.route('/hello/')
@app.route('/hello/<name>')
def hello(name=None):
    return render_template('hello.html', name=name)



