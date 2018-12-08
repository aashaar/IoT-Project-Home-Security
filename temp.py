import os

from flask import render_template, Flask

app = Flask(__name__)


@app.route('/')
def something():
    pics = os.listdir('./static/images')
    # hists = [os.path.join(os.getcwd() + '/static/images', file) for file in hists]
    return render_template('report.html', hists=pics)


if __name__ == '__main__':
    app.run()

# import os
#
# path = os.getcwd() + "/images"
# list_of_files = {}
#
# for filename in os.listdir(path):
#     list_of_files[filename] = "http://127.0.0.1/" + filename
