from flask import Flask
from flask import escape  # converts the characters &, <, >, ‘, and ” in string s to HTML-safe sequences
from flask import redirect
from flask import render_template
from flask import request  # remembers the matched endpoint and view arguments
from flask import session  # object works pretty much like an ordinary dict, with the difference that it keeps track of modifications
from flask import url_for  # generates a URL to the given endpoint with the method provided

app = Flask(__name__)

# set the secret key, keep this really secret,
# storing it as-is just for demonstrating purposes
app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'

@app.route('/')
def index():
    return render_template(
        'template.html', 
        username=session.get('username', None)
    )

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('index'))
    return '''
        <form method="post">
            <p><input type=text name=username>
            <p><input type=submit value=Login>
        </form>
    '''

@app.route('/logout')
def logout():
    # remove the username from the session if it's there
    session.pop('username', None)
    return redirect(url_for('index'))
