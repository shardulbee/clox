#ifndef PARSER_H
#define PARSER_H

#include <ast.h>
#include <linked_list.h>
#include <token.h>

ast_node *parse(linked_list *tokens);

#endif
