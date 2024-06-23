#include "routing.h"
#include <stdio.h>

struct Route *routehead = NULL;

void add_route(char *key, char *value) {
  struct Route *temp = (struct Route *)malloc(sizeof(struct Route));
  temp->key = key;
  temp->value = value;
  temp->next = NULL;
  if (routehead == NULL) {
    routehead = temp;
    return;
  } else {
    struct Route *temp2 = routehead;
    while (temp2->next != NULL) {
      temp2 = temp2->next;
    }
    temp2->next = temp;
  }
}

struct Route *search(char *key) {
  struct Route *temp = routehead;

  while (temp != NULL) {
    if (strcmp(temp->key, key) == 0) {
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

void inorder() {
  struct Route *temp = routehead;
  while (temp != NULL) {
    printf("Key: %s, Value: %s\n", temp->key, temp->value);
    temp = temp->next;
  }
}
