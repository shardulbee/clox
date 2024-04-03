#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "linked_list.h"
#include "parser.h"
#include "token.h"

void test_parse_string() {
  char *input = "\"hello\"";
  linked_list *tokens = lex(input);
  assert(tokens->head != NULL);
  token *tok = tokens->head->value;
  assert(tok->type == STRING);
  assert(strcmp(tok->Literal, "hello") == 0);
  ll_drop(tokens);
}

int main() {
  test_parse_string();
  printf("All tests passed\n");
  return 0;
}
