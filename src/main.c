#include "http_request/http_request.h"
#include "response/response.h"
#include "routing/routing.h"
#include "server/server.h"
#include "string.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

void start(struct Server *server) {
  char buffer[BUFFER_SIZE];
  int new_socket;
  int addrlen = sizeof(server->address);

  struct Route *route = initRoute("/", "index.html");
  addRoute(route, "/about", "about.html");
  inorder(route);

  while (1) {
    printf("Waitng for connections...\n");
    // accept() -> accepts a connection on a socket.
    new_socket = accept(server->sock, (struct sockaddr *)&server->address,
                        (socklen_t *)&addrlen);
    // read() -> read from a file descriptor
    read(new_socket, buffer, BUFFER_SIZE);

    struct Request request = request_constructor(buffer);
    printf("Route: %s\n", request.URI);

    struct Response *response =
        response_constructor(request.URI, request, route);
    //  printf("Status: %s\n", response->status);
    //  printf("Body: %s\n", response->body);

    char *message =
        malloc(sizeof(unsigned char) *
               (strlen(response->status) + strlen(response->body) + 1));
    snprintf(message, strlen(response->status) + strlen(response->body) + 1,
             "%s%s", response->status, response->body);
    printf("Message: %s\n", message);
    send(new_socket, message, sizeof(message), 0);

    // close the new_socket
    close(new_socket);
    free(route);
    free(response);
    free(message);
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
