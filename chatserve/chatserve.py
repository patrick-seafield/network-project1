#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 1 - chatserve

import socket
import sys
import p1_server
import p1_server_ec

    # Get the server user's handle.
# def get_username():


# main()
if __name__ == '__main__':
    # Check there's a port argument supplied by the user.
    if len(sys.argv) < 2:
        print("USAGE: chatserve.py PORT [--extra-credit]")
        sys.exit(1)
        
    host = '127.0.0.1'
    port = int(sys.argv[1])
    
    # Get the user's username
    print("Enter your user handle (username): ", end='', flush=True)
    username = sys.stdin.readline().strip()
    print("Okay, {0}, waiting for a connection now!".format(username))
    
    # Set up the socket and listen for the chatclient.
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen(5)
        keepListening = True
        while keepListening:
            conn, addr = s.accept()
            print('Connected by: ', addr)
        
            # Run standard server or optionally extra credit server.
            if len(sys.argv) > 2 and sys.argv[2] == '--extra-credit':
                keepListening = p1_server_ec.run_server(conn, username)
            else:
                keepListening = p1_server.run_server(conn, username)

    print("Exiting...")
