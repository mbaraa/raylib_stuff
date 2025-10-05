#include "./src/grid.h"
#include "./src/utils.h"

#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Node {
  Position position;
  Cell cell;
  struct Node *next;
  struct Node *prev;
} Node;

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

/*
Node *node_add_prev(Node *node, Vector2 prev_position, Vector2 prev_size) {
  node->prev = node_new(prev_position, prev_size);
  node->prev->next = node;
  return node->prev;
}
*/

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

Snake *snake_new(Position initial_position, Cell head_cell, Cell body_cell) {
  Snake *snake = (Snake *)malloc(sizeof(Snake));
  snake->head = node_new(initial_position, head_cell);
  snake->tail = snake->head;
  snake->last_direction = LEFT;
  snake->head_color = head_cell.color;
  snake->body_color = body_cell.color;
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
    new_position.y--;
    break;
  case DOWN:
    new_position.y++;
    break;
  case RIGHT:
    new_position.x++;
    break;
  case LEFT:
    new_position.x--;
    break;
  }
  snake->last_direction = new_direction;

  Node *new_head = node_new(new_position, (Cell){snake->head_color});
  snake->head->cell.color = snake->body_color;
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

Position place_food(Grid *grid) {
  Position position = {
      .x = GetRandomValue(0, grid->cells_count_sqrt - 1),
      .y = GetRandomValue(0, grid->cells_count_sqrt - 1),
  };

  while (!grid_is_cell_empty(grid, position)) {
    SetRandomSeed(time(NULL));
    position = (Position){
        .x = GetRandomValue(0, grid->cells_count_sqrt - 1),
        .y = GetRandomValue(0, grid->cells_count_sqrt - 1),
    };
  }

  return position;
}

int main(void) {
  Grid *grid = grid_create(10, 69, DARKGREEN);
  Position window_size = grid_get_window_size(grid);
  printf("w: %d, h: %d\n", window_size.x, window_size.y);

  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_size.x, window_size.y, "Snake!");
  SetTargetFPS(15);

  const Color snake_head_color = DARKPURPLE;
  const Color snake_body_color = PURPLE;
  const Color apple_color = RED;
  Position apple_position = place_food(grid);

  Snake *snake = snake_new(
      (Position){
          .x = grid->cells_count_sqrt / 2,
          .y = grid->cells_count_sqrt / 2,
      },
      (Cell){.color = snake_head_color}, (Cell){.color = snake_body_color});

  int score = 0;

  while (!WindowShouldClose()) {
    grid_reset(grid);
    snake_update_position_key(snake);
    snake_update_position(snake);
    printf("apple: x %d y %d\n", apple_position.x, apple_position.y);
    printf("head: x %d y %d\n", snake->head->position.x,
           snake->head->position.y);
    if (snake->head->position.x == apple_position.x &&
        snake->head->position.y == apple_position.y) {
      apple_position = place_food(grid);
      snake_grow(snake);
      score++;
    }

    BeginDrawing();

    ClearBackground(BLACK);
    snake_draw(snake, grid);
    grid_fill_cell(grid, apple_position, (Cell){.color = apple_color});
    grid_draw(grid);
    DrawText(TextFormat("%d", score), window_size.x - 40, 20, 40, BLACK);

    EndDrawing();

    usleep(1000000 / 60);
  }

  grid_destroy(grid);
  snake_destroy(snake);
  CloseWindow();

  return 0;
}
