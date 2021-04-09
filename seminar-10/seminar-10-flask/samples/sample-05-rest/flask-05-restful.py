from flask import Flask
from flask import abort
from flask import jsonify
from flask import request
from sqlite3 import connect


app = Flask(__name__)


@app.route('/tasks/all', methods=['GET'])
def tasks_all():
    conn = connect('tasks.db')
    cur = conn.cursor()
    cur.execute('SELECT id, title, description, done FROM tasks')
    rows = cur.fetchall()
    conn.close()
    return jsonify({
        "total": len(rows),
        "tasks": [
            {
                "id": row[0],
                "title": row[1],
                "description": row[2],
                "done": row[3]
            }
            for row in rows
        ]
    })


@app.route('/tasks/all/done', methods=['GET'])
def tasks_all_done():
    conn = connect('tasks.db')
    cur = conn.cursor()
    cur.execute('SELECT id, title, description, done FROM tasks WHERE done=1')
    rows = cur.fetchall()
    conn.close()
    return jsonify({
        "total": len(rows),
        "tasks": [
            {
                "id": row[0],
                "title": row[1],
                "description": row[2],
                "done": row[3]
            }
            for row in rows
        ]
    })


@app.route('/tasks/all/undone', methods=['GET'])
def tasks_all_undone():
    conn = connect('tasks.db')
    cur = conn.cursor()
    cur.execute('SELECT id, title, description, done FROM tasks WHERE done=0')
    rows = cur.fetchall()
    conn.close()
    return jsonify({
        "total": len(rows),
        "tasks": [
            {
                "id": row[0],
                "title": row[1],
                "description": row[2],
                "done": row[3]
            }
            for row in rows
        ]
    })


@app.route('/tasks/task/<int:task_id>', methods=['GET'])
def tasks_task(task_id):
    conn = connect('tasks.db')
    cur = conn.cursor()
    cur.execute(f'SELECT id, title, description, done FROM tasks WHERE id={task_id}')
    row = cur.fetchone()
    conn.close()
    if not row:
        abort(404)
    return jsonify({
        "id": row[0],
        "title": row[1],
        "description": row[2],
        "done": row[3]
    })
    
    
@app.route('/tasks/task/new', methods=['POST'])
def tasks_task_new():
    if not request.json or not 'title' in request.json:
        abort(400)
    title = request.json['title']
    description = request.json.get('description', '')
    done = False
    conn = connect('tasks.db')
    cur = conn.cursor()
    cur.execute(f'''
        INSERT INTO
            tasks(title, description, done)
        VALUES
            ("{title}", "{description}", {done})
    ''')
    conn.commit()
    conn.close()
    return jsonify({
        "success": True
    })


@app.route('/tasks/task/finish', methods=['POST'])
def tasks_task_finish():
    if not request.json or not 'id' in request.json:
        abort(400)
    id_ = request.json['id']
    conn = connect('tasks.db')
    cur = conn.cursor()
    cur.execute(f'SELECT id, title, description, done FROM tasks WHERE id={id_}')
    row = cur.fetchone()
    if not row:
        conn.close()
        abort(404)
    cur.execute(f'''UPDATE tasks SET done=1 WHERE id={id_}''')
    conn.commit()
    conn.close()
    return jsonify({
        "success": True,
        "task": {
            "id": row[0],
            "title": row[1],
            "description": row[2],
            "done": True
        }
    })
