#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#include "connect.h"


int chatserve_connect(char * hostname, char * port)
{
    // Get the address for our chatserve program.
  int status, sockfd;
  struct addrinfo hints;
  struct addrinfo * chatserver_info, * p;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(hostname, port, &hints, &chatserver_info)) != 0)
  {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  // Set up the connection with the chatserve program.
  for (p = chatserver_info; p != NULL; p = p->ai_next)
  {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
    {
      perror("client: socket");
      continue;
    }
    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
    {
      close(sockfd);
      perror("client: connect");
      continue;
    }
    break;
  }
  
  // Make sure at least one of the IP addressess were able to connect.
  if (p == NULL)
  {
    perror("Failed to connect socket.");
    exit(1);
  }

  freeaddrinfo(chatserver_info);
  return sockfd;
}
