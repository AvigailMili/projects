from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)
client = MongoClient("mongodb://localhost:27017")  # Connect to MongoDB

# Select the database and collection
db = client["mydatabase"]
collection = db["mycollection"]

# Create
@app.route("/items", methods=["POST"])
def create_item():
    data = request.get_json()
    inserted_item = collection.insert_one(data)
    return jsonify({"message": "Item created successfully", "inserted_id": str(inserted_item.inserted_id)})

# Read
@app.route("/items", methods=["GET"])
def get_all_items():
    items = list(collection.find())
    return jsonify(items)

@app.route("/items/<item_id>", methods=["GET"])
def get_item(item_id):
    item = collection.find_one({"_id": item_id})
    if item:
        return jsonify(item)
    else:
        return jsonify({"message": "Item not found"}), 404

# Update
@app.route("/items/<item_id>", methods=["PUT"])
def update_item(item_id):
    data = request.get_json()
    updated_item = collection.update_one({"_id": item_id}, {"$set": data})
    if updated_item.modified_count > 0:
        return jsonify({"message": "Item updated successfully"})
    else:
        return jsonify({"message": "Item not found"}), 404

# Delete
@app.route("/items/<item_id>", methods=["DELETE"])
def delete_item(item_id):
    deleted_item = collection.delete_one({"_id": item_id})
    if deleted_item.deleted_count > 0:
        return jsonify({"message": "Item deleted successfully"})
    else:
        return jsonify({"message": "Item not found"}), 404

if __name__ == "__main__":
    app.run(debug=True)
