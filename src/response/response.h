#ifndef RESPONSE_H
#define RESPONSE_H
#include "../http_request/http_request.h"
#include <stdlib.h>
#include <string.h>

struct Response {
  char *status;
  char *body;
};

struct Response *response_constructor(char *route, struct Request request);
char *render_file(char *filename, struct Response *response);

#endif // RESPONSE_H
