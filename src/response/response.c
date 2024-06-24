#include "response.h"
#include "../server/server.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

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

const char *get_file_extension(const char *filepath) {
  const char *dot = strrchr(filepath, '.'); // Find the last occurrence of '.'
  if (!dot || dot == filepath)
    return ""; // No extension found or dot is the first character

  return dot + 1; // Return the extension (skip the dot character)
}

struct Response response_constructor(char *route, char *filename,
                                     struct Request request, char *status) {
  char *header = (char *)malloc(BUFFER_SIZE * sizeof(char));
  struct Response res;

  size_t response_len = 0;
  char *response = (char *)malloc(BUFFER_SIZE * sizeof(char));
  snprintf(header, BUFFER_SIZE, "%s", status);

  int file_fd = open(filename, O_RDONLY);

  struct stat file_stat;
  fstat(file_fd, &file_stat);

  // copy header to response buffer
  response_len = 0;
  memcpy(response, header, strlen(header));
  response_len += strlen(header);

  // copy file to response buffer
  ssize_t bytes_read;
  while ((bytes_read = read(file_fd, response + response_len,
                            BUFFER_SIZE - response_len)) > 0) {
    response_len += bytes_read;
  }
  res.body = response;
  res.size = response_len;
  res.status = status;
  return res;
  free(header);
  close(file_fd);
}
