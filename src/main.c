#include "server/server.h"
#include "string.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

void start(struct Server *server) {
  char buffer[BUFFER_SIZE];
  char *message = "Hello from the server!";
  int new_socket;
  int addrlen = sizeof(server->address);
  while (1) {
    printf("Waitng for connections...\n");
    // accept() -> accepts a connection on a socket.
    new_socket = accept(server->sock, (struct sockaddr *)&server->address,
                        (socklen_t *)&addrlen);
    // read() -> read from a file descriptor
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Message: %s\n", buffer);

    // write() -> write to a file descriptor
    write(new_socket, message, strlen(message));

    // close the new_socket
    close(new_socket);
  }
}

int main() {
  // AF_INET -> IPv4, SOCK_STREAM -> TCP, 0 -> protocol
  // BACKLOG -> number of connections that can be queued -> 10
  // INADDR_ANY -> any interface
  struct Server server =
      server_constructor(AF_INET, SOCK_STREAM, 0, PORT, 10, INADDR_ANY, start);

  server.start(&server);

  return 0;
}
