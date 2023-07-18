from flask import Flask, jsonify, request
import json

app = Flask(__name__)

# File path for data storage
DATA_FILE = 'books.json'

# Helper function to read data from the file
def read_data():
    try:
        with open(DATA_FILE, 'r') as file:
            data = json.load(file)
    except FileNotFoundError:
        data = []
    return data

# Helper function to write data to the file
def write_data(data):
    with open(DATA_FILE, 'w') as file:
        json.dump(data, file)

# Routes for CRUD operations
@app.route('/books', methods=['GET'])
def get_books():
    books = read_data()
    return jsonify(books)

@app.route('/books', methods=['POST'])
def create_book():
    data = read_data()
    new_book = {
        'id': len(data) + 1,
        'title': request.json['title'],
        'author': request.json['author']
    }
    data.append(new_book)
    write_data(data)
    return jsonify(new_book), 201

@app.route('/books/<int:book_id>', methods=['GET'])
def get_book(book_id):
    data = read_data()
    book = next((book for book in data if book['id'] == book_id), None)
    if book:
        return jsonify(book)
    return jsonify({'error': 'Book not found'}), 404

@app.route('/books/<int:book_id>', methods=['PUT'])
def update_book(book_id):
    data = read_data()
    book = next((book for book in data if book['id'] == book_id), None)
    if book:
        book['title'] = request.json.get('title', book['title'])
        book['author'] = request.json.get('author', book['author'])
        write_data(data)
        return jsonify(book)
    return jsonify({'error': 'Book not found'}), 404

@app.route('/books/<int:book_id>', methods=['DELETE'])
def delete_book(book_id):
    data = read_data()
    book = next((book for book in data if book['id'] == book_id), None)
    if book:
        data.remove(book)
        write_data(data)
        return jsonify({'message': 'Book deleted'})
    return jsonify({'error': 'Book not found'}), 404

# Start the server
if __name__ == '__main__':
    app.run()
1