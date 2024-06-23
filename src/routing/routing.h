#ifndef ROUTING_H
#define ROUTING_H
#include <stdlib.h>
#include <string.h>

// Binary Search Tree huh
struct Route {
  char *key;
  char *value;

  struct Route *left, *right;
};

struct Route *initRoute(char *key, char *value);

struct Route *addRoute(struct Route *root, char *key, char *value);

struct Route *search(struct Route *root, char *key);

void inorder(struct Route *root);
#endif // ROUTING_H
