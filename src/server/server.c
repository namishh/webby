#include "server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_constructor(int domain, int service, int protocol,
                                 int port, int backlog, u_long interface,
                                 void (*start)(struct Server *server)) {
  struct Server server;
  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.port = port;
  server.backlog = backlog;
  server.interface = interface;
  server.start = start;

  server.address.sin_family = domain;
  // htons -> host to network short. converts port to network byte order
  server.address.sin_port = htons(port);
  // htonl -> host to network long. converts interface to network byte order
  server.address.sin_addr.s_addr = htonl(interface);

  /* sockets
  socket() -> create an endpoint for communication. allows os to communicate
  with the network
  domain -> communication domain service -> communication
  semantics protocol -> communication protocol
  */
  server.sock = socket(domain, service, protocol);

  if (server.sock == 0) {
    // perror() -> print a system error message
    perror("Failed to create Socket");
    exit(1); // irregular exiting of the program
  }

  if (setsockopt(server.sock, SOL_SOCKET, SO_REUSEADDR, &(int){1},
                 sizeof(int)) < 0)
    perror("setsockopt(SO_REUSEADDR) failed");

  // bind() -> binds sockets to a network
  int b = bind(server.sock, (struct sockaddr *)&server.address,
               sizeof(server.address));

  if (b < 0) {
    perror("Failed to bind Socket");
    exit(1);
  }

  // Listening for connections. Waits for incoming connections and upon
  // receiving and then does something.
  int l = listen(server.sock, server.backlog);

  if (l < 0) {
    perror("Failed to listen on Socket");
    exit(1);
  }

  return server;
}
