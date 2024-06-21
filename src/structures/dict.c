// Dictionary implmentation in C (:sob:) this made my cry
#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int hash(char *key) {
  unsigned long int hash = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    hash = 31 * hash + key[i];
  }
  return hash % 100;
}

Dictionary *dictionary_constructor() {
  Dictionary *dictionary = (Dictionary *)malloc(sizeof(Dictionary));
  dictionary->items = (Pair **)calloc(100, sizeof(Pair *));
  for (int i = 0; i < 100; i++) {
    dictionary->items[i] = NULL;
  }
  return dictionary;
}

void dictionary_set(Dictionary *dictionary, char *key, char *value) {
  unsigned int index = hash(key);
  Pair *pair = dictionary->items[index];
  Pair *new_pair = (Pair *)malloc(sizeof(Pair));
  new_pair->key = key;
  new_pair->value = value;
  new_pair->next = NULL;
  if (pair == NULL) {
    dictionary->items[index] = new_pair;
    return;
  }
  while (pair->next != NULL) {
    pair = pair->next;
  }
  pair->next = new_pair;
}

char *dictionary_get(Dictionary *dictionary, char *key) {
  unsigned int index = hash(key);
  Pair *pair = dictionary->items[index];
  while (pair != NULL) {
    if (pair->key == key) {
      return pair->value;
    }
    pair = pair->next;
  }
  return NULL;
}

void dictionary_dump(Dictionary *dictionary) {
  for (int i = 0; i < 100; ++i) {
    Pair *pair = dictionary->items[i];
    if (pair == NULL) {
      continue;
    }
    for (;;) {
      printf("%s=%s", pair->key, pair->value);
      if (pair->next == NULL) {
        break;
      }
    }
  }
  printf("\n");
}
