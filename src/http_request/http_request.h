#ifndef HTTP_REQUEST
#define HTTP_REQUEST

struct Request {
  char *method;
  char *URI;
  float HTTPVersion;
  char *body;
  struct Header *request_headers_head;
};

struct Header {
  char *key;
  char *value;
  struct Header *next;
};

struct Request request_constructor(char *string);
void request_add_header(struct Header *head, char *key, char *value);
struct Header *request_get_header(struct Header *head, char *key);
void print_headers(struct Header *head);

#endif // HTTP_REQUEST
