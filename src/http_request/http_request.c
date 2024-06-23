#include "http_request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Header *head = NULL;
struct HeaderString *heads = NULL;

void request_add_headerstring(char *string) {
  struct HeaderString *temp =
      (struct HeaderString *)malloc(sizeof(struct HeaderString));
  temp->next = NULL;
  temp->string = strdup(string);
  if (heads == NULL) {
    heads = temp;
    return;
  } else {
    struct HeaderString *temp2 = heads;
    while (temp2->next != NULL) {
      temp2 = temp2->next;
    }
    temp2->next = temp;
  }
}

void request_add_header(char *key, char *value) {
  struct Header *temp = (struct Header *)malloc(sizeof(struct Header));
  temp->key = key;
  temp->value = value;
  temp->next = NULL;
  if (head == NULL) {
    head = temp;
    return;
  } else {
    struct Header *temp2 = head;
    while (temp2->next != NULL) {
      temp2 = temp2->next;
    }
    temp2->next = temp;
  }
}

struct Header *request_get_header(struct Header *head, char *key) {
  struct Header *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->key, key) == 0) {
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

void print_headers() {
  struct Header *temp = head;
  printf("===========Headers==========\n");
  while (temp != NULL) {
    printf("%s: %s\n", temp->key, temp->value);
    temp = temp->next;
  }
}

// DONE: parse headers. i am blasting my head for this
void parse_headers(char *header_fields) {
  char fields[strlen(header_fields)];
  strcpy(fields, header_fields);
  char *field = strtok(fields, "\n");
  while (field) {
    if (field[0] == '\n') {
      continue;
    }
    char f[strlen(field)];
    strcpy(f, field);
    request_add_headerstring(field);
    field = strtok(NULL, "\n");
  }
  struct HeaderString *temp = heads;
  while (temp != NULL) {
    char *field = strtok(temp->string, ":");
    char *key = field;
    char *value = strtok(NULL, "\0");
    request_add_header(key, value);
    temp = temp->next;
  }
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

  request.method = method;
  request.URI = URI;
  request.HTTPVersion = (float)atof(HTTPVersion);

  parse_headers(header_fields);

  request.request_headers_head = head;
  print_headers();

  return request;
}
