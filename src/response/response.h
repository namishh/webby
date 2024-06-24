#ifndef RESPONSE_H
#define RESPONSE_H
#include "../http_request/http_request.h"
#include <stdlib.h>
#include <string.h>

struct Response {
  char *status;
  char *body;
  size_t size;
};

struct Response response_constructor(char *route, char *filename,
                                     struct Request request, char *status);
char *render_file(char *filename);

#endif // RESPONSE_H
