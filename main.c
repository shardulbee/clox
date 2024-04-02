#include <stdio.h>
#include <stdlib.h>

typedef enum {
  // ILLEGAL represents a token type for errors or unknown tokens.
  // iota is used to automatically increment the numeric value of the constants
  // that follow, providing a unique value for each TokenType.
  ILLEGAL,
  END_OF_FILE,

  // Identifiers + literals
  // Identifiers are user-defined names for variables, functions, etc.
  // Literals are fixed values like numbers, strings, etc.
  IDENT,
  INT,
  STRING,

  // Operators
  // Operators are special symbols that represent computations like addition,
  // subtraction, etc.
  // The operator tokens are the actual characters like +, -, etc.
  PLUS,
  ASSIGN,
  MINUS,
  BANG,
  ASTERISK,
  SLASH,

  LT,
  GT,
  EQ,
  NOT_EQ,

  // Delimiters
  // Delimiters are special symbols that are used to separate tokens.
  // The delimiter tokens are the actual characters like (, ), etc.
  COMMA,
  COLON,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  LBRACKET,
  RBRACKET,

  // Keywords
  // Keywords are reserved words that have special meaning in the language.
  // The keyword tokens are the actual words like fn, let, etc.
  FUNCTION,
  LET,
  IF,
  ELSE,
  RETURN,
  TRUE,
  FALSE,
  FOR,
} token_type;

typedef struct {
  token_type type;
  char *Literal;
} token;

typedef struct {
} ast_node;

typedef struct linked_list_node {
  void *value;
  struct linked_list_node *next;
  struct linked_list_node *prev;
} linked_list_node;

typedef struct {
  linked_list_node *head;
  linked_list_node *tail;
} linked_list;

int ll_push_front(linked_list *list, void *value) {
  // adding in front

  linked_list_node *new_node = malloc(sizeof(linked_list_node));
  if (!new_node) {
    return 1;
  }

  new_node->value = value;

  if (!list->head) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    new_node->next = list->head;
    list->head->prev = new_node;
    list->head = new_node;
  }

  return 0;
}

int ll_push_back(linked_list *list, void *value) {
  // adding in back
  linked_list_node *new_node = malloc(sizeof(linked_list_node));
  if (!new_node) {
    return 1;
  }
  new_node->value = value;
  if (!list->head) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    new_node->prev = list->tail;
    list->tail->next = new_node;
    list->tail = new_node;
  }
  return 0;
}

int ll_drop(linked_list *list) {
  linked_list_node *current = list->head;
  linked_list_node *next;
  while (current) {
    next = current->next;
    free(current);
    current = next;
  }
  free(list);
  return 0;
}

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

typedef struct read_result {
  char *value;
  int length;
} read_result;

read_result read_number(char *source, int i) {
  int start = i;
  while (source[i] >= '0' && source[i] <= '9') {
    i++;
  }
  char *number = malloc(i - start + 1);
  for (int j = 0; j < i - start; j++) {
    number[j] = source[start + j];
  }
  read_result result = {number, i - start};
  return result;
}

read_result read_identifier(char *source, int i) {
  int start = i;
  while ((source[i] >= 'a' && source[i] <= 'z') ||
         (source[i] >= 'A' && source[i] <= 'Z')) {
    i++;
  }
  char *identifier = malloc(i - start + 1);
  for (int j = 0; j < i - start; j++) {
    identifier[j] = source[start + j];
  }
  read_result result = {identifier, i - start};
  return result;
}

read_result read_string(char *source, int i) {
  int start = i;
  while (source[i] != '"' && source[i] != '\0') {
    i++;
  }
  char *string = malloc(i - start + 1);
  for (int j = 0; j < i - start; j++) {
    string[j] = source[start + j];
  }
  read_result result = {string, i - start};
  return result;
}

linked_list *lex(char *source) {
  linked_list *tokens = malloc(sizeof(linked_list));

  for (int i = 0; source[i] != '\0'; i++) {
    token *tok = malloc(sizeof(token));
    printf("Starting iteration. i=%d, source[i]=%c\n", i, source[i]);
    switch (source[i]) {
    case '+':
      tok->type = PLUS;
      tok->Literal = "+";
      ll_push_back(tokens, tok);
      break;
    case '-':
      tok->type = MINUS;
      tok->Literal = "-";
      ll_push_back(tokens, tok);
      break;
    case '*':
      tok->type = ASTERISK;
      tok->Literal = "*";
      ll_push_back(tokens, tok);
      break;
    case '/':
      tok->type = SLASH;
      tok->Literal = "/";
      ll_push_back(tokens, tok);
      break;
    case '(':
      tok->type = LPAREN;
      tok->Literal = "(";
      ll_push_back(tokens, tok);
      break;
    case ')':
      tok->type = RPAREN;
      tok->Literal = ")";
      ll_push_back(tokens, tok);
      break;
    case '{':
      tok->type = LBRACE;
      tok->Literal = "{";
      ll_push_back(tokens, tok);
      break;
    case '}':
      tok->type = RBRACE;
      tok->Literal = "}";
      ll_push_back(tokens, tok);
      break;
    case '[':
      tok->type = LBRACKET;
      tok->Literal = "[";
      ll_push_back(tokens, tok);
      break;
    case ']':
      tok->type = RBRACKET;
      tok->Literal = "]";
      ll_push_back(tokens, tok);
      break;
    case ',':
      tok->type = COMMA;
      tok->Literal = ",";
      ll_push_back(tokens, tok);
      break;
    case ';':
      tok->type = SEMICOLON;
      tok->Literal = ";";
      ll_push_back(tokens, tok);
      break;
    case ':':
      tok->type = COLON;
      tok->Literal = ":";
      ll_push_back(tokens, tok);
      break;
    case '<':
      tok->type = LT;
      tok->Literal = "<";
      ll_push_back(tokens, tok);
      break;
    case '>':
      tok->type = GT;
      tok->Literal = ">";
      ll_push_back(tokens, tok);
      break;
    case '=':
      if (source[i + 1] == '=') {
        tok->type = EQ;
        tok->Literal = "==";
      } else {
        tok->type = ASSIGN;
        tok->Literal = "=";
      }
      ll_push_back(tokens, tok);
      break;
    case '!':
      if (source[i + 1] == '=') {
        tok->type = NOT_EQ;
        tok->Literal = "!=";
      } else {
        tok->type = BANG;
        tok->Literal = "!";
      }
      ll_push_back(tokens, tok);
      break;
    case ' ':
      break;
    case '\t':
      break;
    case '\n':
      break;
    case '\r':
      break;
    case '\f':
      break;
    case '\v':
      break;
    case '\0':
      tok->type = END_OF_FILE;
      tok->Literal = "";
      ll_push_back(tokens, tok);
      break;
    case '"':
      tok->type = STRING;
      read_result str = read_string(source, i + 1);
      tok->Literal = str.value;
      i += str.length + 1;
      ll_push_back(tokens, tok);
      break;
    default:
      if (source[i] >= '0' && source[i] <= '9') {
        tok->type = INT;
        read_result num = read_number(source, i);
        tok->Literal = num.value;
        i += num.length - 1;
        ll_push_back(tokens, tok);
      } else if ((source[i] >= 'a' && source[i] <= 'z') ||
                 (source[i] >= 'A' && source[i] <= 'Z')) {
        tok->type = IDENT;
        read_result ident = read_identifier(source, i);
        tok->Literal = ident.value;
        i += ident.length - 1;
        ll_push_back(tokens, tok);
      } else {
        printf("Usage: unhandled token %c\n", source[i]);
        return NULL;
      }
    }
    printf("Incrementing i. old=%d, new=%d\n", i, i + 1);
  }
  return tokens;
}

ast_node *parse(linked_list *tokens) {
  ast_node *ast = malloc(sizeof(ast_node));
  return ast;
}

void *interpret(ast_node *ast) { return NULL; }

void print_tokens(linked_list *tokens) {
  linked_list_node *current = tokens->head;
  while (current) {
    token *tok = current->value;
    printf("Token: %d, %s\n", tok->type, tok->Literal);
    current = current->next;
  }
}

void run_file(char *thing) {
  char *source = read_file(thing);
  linked_list *tokens = lex(source);
  free(source);

  ast_node *ast = parse(tokens);
  print_tokens(tokens);
  free(tokens);

  void *result = interpret(ast);
  free(ast);

  return;
}

void run_prompt() { return; }

int main(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 64; // SYSEXITS(3)
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    run_prompt();
  }
  printf("Good stuff\n");

  return 0;
}
