#ifndef DICT
#define DICT

typedef struct Pair {
  char *key;
  char *value;
  struct Pair *next;
} Pair;

typedef struct {
  Pair **items;
} Dictionary;

Dictionary *dictionary_constructor();
void dictionary_set(Dictionary *dictionary, char *key, char *value);
char *dictionary_get(Dictionary *dictionary, char *key);
void dictionary_dump(Dictionary *dictionary);

#endif // DICT
