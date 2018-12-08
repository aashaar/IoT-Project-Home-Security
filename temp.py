import os

from flask import render_template, Flask

app = Flask(__name__)


@app.route('/')
def something():
    hists = os.listdir('images')
    hists = [file for file in hists]
    return render_template('report.html', hists=hists)


if __name__ == '__main__':
    app.run()
    something()
