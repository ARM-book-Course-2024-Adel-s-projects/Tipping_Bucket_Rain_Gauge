import socket

HOST = '192.168.0.9'
PORT = 2323

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()
print(f"Listening in port {PORT}")

try:
    conn, addr = server_socket.accept()
    print(f"Accepted connection from {addr}")

    while True:
        data = conn.recv(1024)
        if not data:
            break
        print(f"Received: {data.decode('utf-8')}")
        conn.sendall(b"Message received")

except KeyboardInterrupt:
    print("\nServer interrupted by user. Closing connection...")

finally:
    if conn:
        conn.close()
    server_socket.close()
    print("Server socket closed.")

