#ifndef _NODE_H
#define _NODE_H

#include "./grid.h"

typedef struct Node {
  Position position;
  Cell cell;
  struct Node *next;
  struct Node *prev;
} Node;

Node *node_new(Position position, Cell cell);
Node *node_add_next(Node *node, Position next_position, Cell next_cell);
void node_destroy(Node *node);

#endif
