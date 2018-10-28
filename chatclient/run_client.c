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
  int bytes_sent;
  
  do
  {
    // Get a line from the user to send.
    memset(&buf, 0, sizeof(buf));
    memset(message, 0, message_max);
    printf("%s> ", username);
    if (getline(&message, &message_max, stdin) == -1) {
      perror("Problem getting line from user.");
      exit(1);
    }

    // Send the username and message to the server
    snprintf(buf, sizeof(buf), "%s> %s", username, message);
    bytes_sent = send(sockfd, buf, MESSAGE_LENGTH, 0);
    
  } while (0);

  free(message);
}

