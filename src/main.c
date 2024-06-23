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
  add_route("/", "index.html");
  add_route("/about", "about.html");
  inorder();
  while (1) {
    printf("Waitng for connections...\n");
    // accept() -> accepts a connection on a socket.
    new_socket = accept(server->sock, (struct sockaddr *)&server->address,
                        (socklen_t *)&addrlen);
    // read() -> read from a file descriptor
    read(new_socket, buffer, BUFFER_SIZE);

    struct Request request = request_constructor(buffer);
    printf("Route: %s\n", request.URI);

    char *status = "HTTP/1.1 200 OK\r\n\r\n";
    char *file;

    struct Route *route = search(request.URI);
    if (route == NULL) {
      status = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
      file = "./public/404.html";
      printf("Route not found\n");
    } else {
      char filename[100];
      snprintf(filename, 100, "./public/%s", route->value);
      printf("Route found %s\n", filename);
      file = strdup(filename);
    }

    struct Response response = response_constructor(status, file, request);
    printf("Status: %s\n", response.status);
    printf("Body: %s\n", response.body);

    char *message = malloc(sizeof(unsigned char) * (strlen(response.status) +
                                                    strlen(response.body) + 1));
    sprintf(message, "%s%s", response.status, response.body);

    send(new_socket, message, strlen(message), 0);

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
