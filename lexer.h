#include "linked_list.h"

typedef struct read_result {
  char *value;
  int length;
} read_result;
linked_list *lex(char *source);
