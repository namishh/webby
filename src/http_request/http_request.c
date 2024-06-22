#include "http_request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Header *head;

void request_add_header(struct Header *head, char *key, char *value) {
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

void print_headers(struct Header *head) {
  struct Header *temp = head;
  printf("===========Headers==========\n");
  while (temp != NULL) {
    printf("%s: %s\n", temp->key, temp->value);
    temp = temp->next;
  }
}

// TODO: parse headers. i am blasting my head for this
void parse_headers(char *header_fields) {
  char *token = NULL;
  token = strtok(header_fields, "\n");
  while (token) {
    token = strtok(NULL, "\n");
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
  print_headers(head);

  request.request_headers_head = head;

  return request;
}
