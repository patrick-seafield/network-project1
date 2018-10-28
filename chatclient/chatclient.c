#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "connect.h"
#include "run_client.h"
#include "run_client_ec.h"

char * ec_flag = "--extra-credit";

int main(int argc, char **argv)
{
  // Check that there's enough arguments to the function.
  if (argc < 3) {
    printf("USAGE %s HOST PORT\n", argv[0]);
    exit(1);
  }

  // Get the username from the user.
  size_t uname_size = 256;
  char * username = malloc(uname_size * sizeof(char));
  printf("Enter your user handle (username): ");
  if (getline(&username, &uname_size, stdin) == -1) {
    perror("Unable to getline: username.\n");
    exit(1);
  }
  // Remove the \n character from the username.
  char *pos;
  if (( pos = strchr(username, '\n')) != NULL)
  {
    *pos = '\0';
  }
  
  // Connect to the chat server and run the client. Optionally run the extra
  // credit client if the flag has been passed.
  int sockfd = chatserve_connect(argv[1], argv[2]);
  if (argc == 4 && strcmp(argv[3], ec_flag) == 0)
  {
    run_client_ec(sockfd, username, uname_size);
  } 
  else 
  {
    run_client(sockfd, username, uname_size);
  }

  // Clean up and exit.
  free(username);
  close(sockfd);
  exit(0);
}
