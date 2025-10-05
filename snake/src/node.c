#include "./node.h"
#include <stdlib.h>

Node *node_new(Position position, Cell cell) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->next = NULL;
  node->prev = NULL;
  node->position = position;
  node->cell = cell;

  return node;
}

Node *node_add_next(Node *node, Position next_position, Cell next_cell) {
  node->next = node_new(next_position, next_cell);
  node->next->prev = node;
  return node->next;
}

void node_destroy(Node *node) {
  if (node == NULL) {
    return;
  }
  if (node->next == NULL) {
    return;
  }
  node_destroy(node->next);
  free(node);
  node = NULL;
}
