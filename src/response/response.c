#include "response.h"
#include "../routing/routing.h"
#include <stdio.h>

char *render_file(char *filename, struct Response *response) {
  FILE *file = fopen(filename, "r");
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *temp = malloc(sizeof(char) * (fsize + 1));
  char ch;
  int i = 0;
  while ((ch = fgetc(file)) != EOF) {
    temp[i] = ch;
    i++;
  }
  fclose(file);
  return temp;
}

struct Response *response_constructor(char *route, struct Request request) {
  char filename[100];
  struct Response *response = malloc(sizeof(struct Response));
  struct Route *r = search(route);

  if (r->value == NULL) {
    sprintf(filename, "./public/404.html");
    response->status = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
    response->body = render_file(filename, response);
  }

  snprintf(filename, 100, "./public/%s", r->value);
  response->status = "HTTP/1.1 200 OK\r\n\r\n";
  response->body = render_file(filename, response);
  printf("%s\n", filename);
  return response;
}
