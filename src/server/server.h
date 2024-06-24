#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 6969
#define BUFFER_SIZE 5000000

struct Server {
  int domain;
  int service;
  int protocol;
  int port;
  int backlog;
  u_long interface;
  struct sockaddr_in address; // IPv4

  int sock;

  void (*start)(struct Server *server);
};

struct Server server_constructor(int domain, int service, int protocol,
                                 int port, int backlog, u_long interface,
                                 void (*start)(struct Server *server));

#endif // !SERVER_H
