#include <lexer.h>
#include <stdlib.h>
#include <token.h>

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
        read_result ident = read_identifier(source, i);
        token_type keyword = lookup_keyword(ident.value);
        if (keyword) {
          tok->type = keyword;
        } else {
          tok->type = IDENT;
        }
        tok->Literal = ident.value;
        i += ident.length - 1;
        ll_push_back(tokens, tok);
      } else {
        return NULL;
      }
    }
  }
  return tokens;
}
