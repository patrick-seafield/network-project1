import socket


def run_server(conn, username):
    with conn:
        while True:
            # Receive data from our client
            data = conn.recv(1024)
            if not data:
                break

            print(data)
            conn.sendall('{0}> {1}'.format(username, data))
