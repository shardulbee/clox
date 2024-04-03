#include "token.h"
#include <string.h>

char *print_token_type(token_type token) {
  switch (token) {
  case ILLEGAL:
    return "ILLEGAL";
  case END_OF_FILE:
    return "END_OF_FILE";
  case IDENT:
    return "IDENT";
  case INT:
    return "INT";
  case STRING:
    return "STRING";
  case PLUS:
    return "PLUS";
  case ASSIGN:
    return "ASSIGN";
  case MINUS:
    return "MINUS";
  case BANG:
    return "BANG";
  case ASTERISK:
    return "ASTERISK";
  case SLASH:
    return "SLASH";
  case LT:
    return "LT";
  case GT:
    return "GT";
  case EQ:
    return "EQ";
  case NOT_EQ:
    return "NOT_EQ";
  case COMMA:
    return "COMMA";
  case COLON:
    return "COLON";
  case SEMICOLON:
    return "SEMICOLON";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case LBRACE:
    return "LBRACE";
  case RBRACE:
    return "RBRACE";
  case LBRACKET:
    return "LBRACKET";
  case RBRACKET:
    return "RBRACKET";
  case FUNCTION:
    return "FUNCTION";
  case LET:
    return "LET";
  case IF:
    return "IF";
  case ELSE:
    return "ELSE";
  case RETURN:
    return "RETURN";
  case TRUE:
    return "TRUE";
  case FALSE:
    return "FALSE";
  case FOR:
    return "FOR";
  default:
    return "UNKNOWN";
  }
}

token_type lookup_keyword(char *ident) {
  if (strcmp(ident, "fn") == 0) {
    return FUNCTION;
  } else if (strcmp(ident, "let") == 0) {
    return LET;
  } else if (strcmp(ident, "if") == 0) {
    return IF;
  } else if (strcmp(ident, "else") == 0) {
    return ELSE;
  } else if (strcmp(ident, "return") == 0) {
    return RETURN;
  } else if (strcmp(ident, "true") == 0) {
    return TRUE;
  } else if (strcmp(ident, "false") == 0) {
    return FALSE;
  } else if (strcmp(ident, "for") == 0) {
    return FOR;
  }
  return 0;
}
