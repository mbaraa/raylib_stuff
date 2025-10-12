#include "./snake.h"
#include "./grid.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Snake *snake_new(Position initial_position, Cell head_cell, Cell body_cell) {
  Snake *snake = (Snake *)malloc(sizeof(Snake));
  snake->head = node_new(initial_position, head_cell);
  snake->tail = snake->head;
  snake->last_direction = LEFT;
  for (size_t i = 0; i < 3; i++) {
    initial_position.x += 1;
    snake->tail = node_add_next(snake->tail, initial_position, body_cell);
  }

  return snake;
}

void snake_destroy(Snake *snake) {
  node_destroy(snake->head);
  free(snake);
  snake = NULL;
}

void snake_grow(Snake *snake) {
  Position grow_at = {
      .x = snake->tail->position.x + 1,
      .y = snake->tail->position.y,
  };
  snake->tail = node_add_next(snake->tail, grow_at, snake->tail->cell);
}

void snake_draw(Snake *snake, Grid *grid) {
  for (Node *node = snake->head; node != NULL; node = node->next) {
    grid_fill_cell(grid, node->position, node->cell);
  }
}

void snake_move(Snake *snake, Direction new_direction) {
  Position new_position = snake->head->position;
  switch (new_direction) {
  case UP:
    if (snake->last_direction == DOWN) {
      return;
    }
    new_position.y--;
    break;
  case DOWN:
    if (snake->last_direction == UP) {
      return;
    }
    new_position.y++;
    break;
  case RIGHT:
    if (snake->last_direction == LEFT) {
      return;
    }
    new_position.x++;
    break;
  case LEFT:
    if (snake->last_direction == RIGHT) {
      return;
    }
    new_position.x--;
    break;
  }
  snake->last_direction = new_direction;

  Node *new_head = node_new(new_position, snake->head->cell);
  snake->head->cell.color = snake->head->next->cell.color;
  new_head->next = snake->head;
  snake->head->prev = new_head;
  snake->head = new_head;

  snake->tail = snake->tail->prev;
  free(snake->tail->next);
  snake->tail->next = NULL;
}

void snake_move_right(Snake *snake) { snake_move(snake, RIGHT); }

void snake_move_left(Snake *snake) { snake_move(snake, LEFT); }

void snake_move_up(Snake *snake) { snake_move(snake, UP); }

void snake_move_down(Snake *snake) { snake_move(snake, DOWN); }

void snake_update_position_key(Snake *snake) {
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
    snake_move_down(snake);
  } else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
    snake_move_up(snake);
  } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D)) {
    snake_move_left(snake);
  } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_A)) {
    snake_move_right(snake);
  }
}

void snake_update_position(Snake *snake) {
  switch (snake->last_direction) {
  case UP:
    snake_move_up(snake);
    break;
  case DOWN:
    snake_move_down(snake);
    break;
  case RIGHT:
    snake_move_right(snake);
    break;
  case LEFT:
    snake_move_left(snake);
    break;
  }
}
