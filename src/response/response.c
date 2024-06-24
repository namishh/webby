#include "response.h"
#include "../server/server.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

const char *get_file_extension(const char *filepath) {
  const char *dot = strrchr(filepath, '.'); // Find the last occurrence of '.'
  if (!dot || dot == filepath)
    return ""; // No extension found or dot is the first character

  return dot + 1; // Return the extension (skip the dot character)
}

const char *get_mime_type(const char *file_ext) {
  if (strcasecmp(file_ext, "html") == 0 || strcasecmp(file_ext, "htm") == 0) {
    return "text/html";
  } else if (strcasecmp(file_ext, "txt") == 0) {
    return "text/plain";
  } else if (strcasecmp(file_ext, "css") == 0) {
    return "text/css";
  } else if (strcasecmp(file_ext, "js") == 0) {
    return "text/javascript";
  } else if (strcasecmp(file_ext, "jpg") == 0 ||
             strcasecmp(file_ext, "jpeg") == 0) {
    return "image/jpeg";
  } else if (strcasecmp(file_ext, "png") == 0) {
    return "image/png";
  } else if (strcasecmp(file_ext, "webp") == 0) {
    return "image/webp";
  } else {
    return "application/octet-stream";
  }
}

struct Response response_constructor(char *route, char *filename,
                                     struct Request request, char *status) {
  char *header = (char *)malloc(BUFFER_SIZE * sizeof(char));
  struct Response res;

  size_t response_len = 0;
  char *response = (char *)malloc(BUFFER_SIZE * sizeof(char));
  snprintf(header, BUFFER_SIZE, "%sContent-Type:%s\r\n\r\n", status,
           get_mime_type(get_file_extension(filename)));

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
