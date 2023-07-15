import http.server
import socketserver

# Set the IP address and port number for the server
IP_ADDRESS = "127.0.0.1"
PORT = 8000

# Define the handler for the server
class MyHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header("Content-type", "text/html")
        self.end_headers()

        # Send the response body
        self.wfile.write(b"Hello, World!")

# Create an instance of the server
with socketserver.TCPServer((IP_ADDRESS, PORT), MyHandler) as server:
    print(f"Server started at {IP_ADDRESS}:{PORT}")

    # Start the server
    server.serve_forever()
