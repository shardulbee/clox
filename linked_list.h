#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list_node {
  void *value;
  struct linked_list_node *next;
  struct linked_list_node *prev;
} linked_list_node;

typedef struct {
  linked_list_node *head;
  linked_list_node *tail;
} linked_list;

int ll_push_front(linked_list *list, void *value);
int ll_push_back(linked_list *list, void *value);
int ll_drop(linked_list *list);

#endif
