import socket

def run_server(conn, username):
    with conn:
        while True:
            # Receive data from our client
            data = conn.recv(1024)
            if not data:
                break
            message = data.split(b'\x00', 1)[0].decode('ascii');
            print(message)
            conn.sendall(b'Received\n')
