#include "http_request.h"
#include <stdlib.h>
#include <string.h>

// i hate this much if else but welp.
int method_select(char *method) {
  if (strcmp(method, "GET") == 0) {
    return GET;
  } else if (strcmp(method, "POST") == 0) {
    return POST;
  } else if (strcmp(method, "PUT") == 0) {
    return PUT;
  } else if (strcmp(method, "DELETE") == 0) {
    return DELETE;
  } else if (strcmp(method, "HEAD") == 0) {
    return HEAD;
  } else if (strcmp(method, "OPTIONS") == 0) {
    return OPTIONS;
  } else if (strcmp(method, "TRACE") == 0) {
    return TRACE;
  } else if (strcmp(method, "CONNECT") == 0) {
    return CONNECT;
  } else if (strcmp(method, "PATCH") == 0) {
    return PATCH;
  }
  return -1;
}

struct Request request_constructor(char *string) {
  // seperate data and body
  for (int i = 0; i < strlen(string) - 1; i++) {
    if (string[i] == '\n' && string[i + 1] == '\n') {
      string[i + 1] = '|';
    }
  }
  char *request_line = strtok(string, "\n");
  char *header_fields =
      strtok(NULL, "|"); // NULL means continue using the line we were using
  char *body = strtok(NULL, "\n");

  struct Request request;

  // stirng parsing :sob:
  char *method = strtok(request_line, " ");
  char *URI = strtok(NULL, " ");
  char *HTTPVersion = strtok(NULL, " ");
  HTTPVersion = strtok(HTTPVersion, "/");
  HTTPVersion = strtok(NULL, "/");

  request.method = method_select(method);
  request.URI = URI;
  request.HTTPVersion = (float)atof(HTTPVersion);

  request.headers = dictionary_constructor();

  char *token = strtok(header_fields, "\n");
  while (token) {
    char *key = strtok(token, ":");
    char *value = strtok(NULL, "\n");
    dictionary_set(request.headers, key, value);
    token = strtok(NULL, "\n");
  }

  return request;
}
