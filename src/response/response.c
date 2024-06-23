#include "response.h"
#include "../routing/routing.h"
#include <stdio.h>

char *render_file(char *filename, struct Response *response) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    response->status = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
    file = fopen("./public/404.html", "r");
  }
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

struct Response *response_constructor(char *route, struct Request request,
                                      struct Route *root) {
  printf("Route 3: %s\n", route);
  struct Route *r = search(root, route);
  char filename[100];
  sprintf(filename, "./public/%s", r->value);
  printf("%s\n", filename);
  struct Response *response = malloc(sizeof(struct Response));
  response->status = "HTTP/1.1 200 OK\r\n\r\n";
  response->body = render_file(filename, response);
  return response;
}
