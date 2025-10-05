#ifndef _SNAKE_H
#define _SNAKE_H

#include "./node.h"

typedef enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT,
} Direction;

typedef struct Snake {
  Node *head;
  Node *tail;
  Direction last_direction;
  Color head_color;
  Color body_color;
} Snake;

Snake *snake_new(Position initial_position, Cell head_cell, Cell body_cell);
void snake_destroy(Snake *snake);
void snake_grow(Snake *snake);
void snake_draw(Snake *snake, Grid *grid);
void snake_move_right(Snake *snake);
void snake_move_left(Snake *snake);
void snake_move_up(Snake *snake);
void snake_move_down(Snake *snake);
void snake_update_position_key(Snake *snake);
void snake_update_position(Snake *snake);

#endif
