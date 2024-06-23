#ifndef ROUTING_H
#define ROUTING_H
#include <stdlib.h>
#include <string.h>

struct Route {
  char *key;
  char *value;
  struct Route *next;
};

void add_route(char *key, char *value);
void inorder();
struct Route *search(char *key);

#endif // ROUTING_H
