#ifndef __run_client_h
#define __run_client_h

#include <stdlib.h>

// Run the chat client program on this socket.
void run_client(int sockfd, char * username, size_t uname_size);

#endif
