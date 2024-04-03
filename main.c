#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lexer.h"
#include "linked_list.h"
#include "parser.h"
#include "token.h"

char *read_file(char *fname) {
  FILE *file = fopen(fname, "r");
  if (!file) {
    fprintf(stderr, "Could not open file '%s'.\n", fname);
    exit(74);
  }

  // get file size so that we know how much memory to allocate
  fseek(file, 0L, SEEK_END);
  size_t file_size = ftell(file);
  char *buffer = malloc(file_size + 1);
  if (!buffer) {
    fprintf(stderr, "Not enough memory to read '%s'.\n", fname);
    exit(74);
  }

  // read file into buffer
  fseek(file, 0L, SEEK_SET);
  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read < file_size) {
    fprintf(stderr, "Could not read file '%s'.\n", fname);
    exit(74);
  }

  // close file
  fclose(file);
  return buffer;
}

void *interpret(ast_node *ast) { return NULL; }

void print_token(token *tok) {
  printf("Token: %s, %s\n", print_token_type(tok->type), tok->Literal);
}

void print_tokens(linked_list *tokens) {
  linked_list_node *current = tokens->head;
  while (current) {
    token *tok = current->value;
    print_token(tok);
    current = current->next;
  }
}

void run(char *input) {
  linked_list *tokens = lex(input);
  ast_node *ast = parse(tokens);
  print_tokens(tokens);
  ll_drop(tokens);

  void *result = interpret(ast);
  free(ast);

  return;
}

void run_file(char *thing) {
  char *source = read_file(thing);
  run(source);
}

void run_prompt() {
  char *line = NULL;
  size_t len = 0;
  ssize_t read = 1;

  while (read > 0) {
    printf(">> ");
    read = getline(&line, &len, stdin);
    if (read == -1) {
      break;
    }

    run(line);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 64;
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    run_prompt();
  }

  return 0;
}
