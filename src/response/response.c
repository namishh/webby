#include "response.h"
#include <stdio.h>

char *render_file(char *filename) {
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

struct Response response_constructor(char *status, char *filename,
                                     struct Request request) {
  struct Response response;
  response.status = status;
  response.body = render_file(filename);

  return response;
}
