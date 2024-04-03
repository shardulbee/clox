#ifndef TOKEN_H
#define TOKEN_H

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

char *print_token_type(token_type token);
token_type lookup_keyword(char *ident);

#endif
