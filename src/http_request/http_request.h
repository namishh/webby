#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include "../structures/dict.h"

enum Methods { GET, POST, PUT, DELETE, HEAD, OPTIONS, TRACE, CONNECT, PATCH };

struct Request {
  int method;
  char *URI;
  float HTTPVersion;
  Dictionary *headers;
};

struct Request request_constructor(char *string);

#endif // HTTP_REQUEST
