#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "constants.h"
#include "run_client.h"

void run_client(int sockfd, char * username, size_t uname_size)
{
  char buf[MESSAGE_LENGTH];
  size_t message_max = MESSAGE_LENGTH - uname_size - 3;
  char * message = malloc(message_max * sizeof(char));
  int bytes_sent, bytes_recv;

  do
  {
    // Get a line from the user to send. If it's \quit, exit the program.
    memset(&buf, 0, sizeof(buf));
    memset(message, 0, message_max);
    printf("%s> ", username);
    if (getline(&message, &message_max, stdin) == -1) {
      perror("Problem getting line from user.");
      exit(1);
    }
    if (strncmp(message, "\\quit", 5) == 0)
    {
      break;
    }

    // Send the username and message to the server
    snprintf(buf, sizeof(buf), "%s> %s", username, message);
    bytes_sent = send(sockfd, buf, MESSAGE_LENGTH, 0);


    // Wait to receive a message from the server.
    memset(&buf, 0, sizeof(buf));
    bytes_recv = recv(sockfd, buf, MESSAGE_LENGTH, 0);
    fwrite(buf, sizeof(buf[0]), strlen(buf), stdout);
    
    // Check if the connection has been closed.
    if (bytes_recv == 0)
    {
      break;
    }


  } while (1);

  free(message);
}

