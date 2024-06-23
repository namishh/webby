#ifndef RESPONSE_H
#define RESPONSE_H
#include "../http_request/http_request.h"
#include "../routing/routing.h"
#include <stdlib.h>
#include <string.h>

struct Response {
  char *status;
  char *body;
};

struct Response *response_constructor(char *route, struct Request request,
                                      struct Route *root);
char *render_file(char *filename, struct Response *response);

#endif // RESPONSE_H
