#ifndef __run_client_ec_h
#define __run_client_ec_h

#include <stdlib.h>


// Run the chat client program on this socket.
void run_client_ec(int sockfd, char * username, size_t uname_size);

#endif
