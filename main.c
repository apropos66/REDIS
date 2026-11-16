#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "parse.h"

int main(void) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("Socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(6380);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(socket_fd, 10) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening on port 6380\n");

  while (1) {

    int conn_fd = accept(socket_fd, NULL, NULL);

    if (conn_fd < 0) {
      perror("accept");
      continue;
    }
    printf("Client connected\n");

    char buf[256];
    char reply[256];
    while (1) {
      ssize_t n = read(conn_fd, buf, sizeof(buf) - 1);
      if (n <= 0) {
        break;
      }
      buf[n] = '\0';
      parse_line(buf, reply, 256);
      ssize_t w = write(conn_fd, reply, strlen(reply));
      if (w <= 0) {
        perror("write");
        exit(EXIT_FAILURE);
      }
    }

    close(conn_fd);
    printf("Client disconnected.");
  }

  close(socket_fd);
  return 0;
}
