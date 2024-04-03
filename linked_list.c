#include <linked_list.h>
#include <stdlib.h>

int ll_push_front(linked_list *list, void *value) {
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
