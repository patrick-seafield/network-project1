import socket
import sys

def run_server(conn, username):
    result = True
    with conn:
        while result:
            # Receive data from our client.
            data = conn.recv(1024)
            if not data:
                break

            #Convert it to a python string and print it.
            message = data.split(b'\x00', 1)[0].decode('ascii');
            print(message)

            # Get a message from the user. Quit if asked, otherwise send it.
            print("{0}> ".format(username), end='', flush=True)
            sendmsg = sys.stdin.readline()
            if sendmsg == "\\quit\n":
                result = False
            else:
                conn.sendall("{0}> {1}".format(username, sendmsg).encode('ascii'))
    return result
