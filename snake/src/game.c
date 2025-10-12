#include "./game.h"
#include "food.h"
#include "grid.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

Snake *new_snake_with_config(GameConfig config) {
  Snake *snake = snake_new(
      (Position){
          .x = config.snake_inital_position.x,
          .y = config.snake_inital_position.y,
      },
      config.snake_head_cell, config.snake_body_cell);

  return snake;
}

Game *game_new(Grid *grid, GameConfig config) {
  Game *game = (Game *)malloc(sizeof(Game));
  game->config = config;
  game->grid = grid;
  game->snake = new_snake_with_config(game->config);
  game->last_food_position = place_food(game->grid);
  game->score = 0;

  return game;
}

void game_destroy(Game *game) {
  snake_destroy(game->snake);
  free(game);
  game = NULL;
}

void game_reset(Game *game) {
  grid_reset(game->grid);
  game->score = 0;
  game->snake = new_snake_with_config(game->config);
  game->last_food_position = place_food(game->grid);
}

double last_event_at = 0.0f;

bool check_event_triggered(double interval) {
  double current_time = GetTime();
  if (current_time - last_event_at >= interval) {
    last_event_at = current_time;
    return true;
  }
  return false;
}

void game_update(Game *game) {
  if (game->snake->head->position.x == game->last_food_position.x &&
      game->snake->head->position.y == game->last_food_position.y) {
    game->last_food_position = place_food(game->grid);
    snake_grow(game->snake);
    game->score++;
  }

  if (game->snake->head->position.x >= game->grid->cells_count_sqrt ||
      game->snake->head->position.x < 0 ||
      game->snake->head->position.y >= game->grid->cells_count_sqrt ||
      game->snake->head->position.y < 0) {
    puts("booo");
    return;
  }

  if (check_event_triggered(0.1f * (double)game->config.speed)) {
    snake_update_position(game->snake);
    snake_update_position_key(game->snake);
  }
  grid_reset(game->grid);
}

void game_draw(Game *game) {
  Position window_size = grid_get_window_size(game->grid);

  grid_fill_cell(game->grid, game->last_food_position,
                 (Cell){.color = game->config.food_color, .roundness = 0.5});
  snake_draw(game->snake, game->grid);
  grid_draw(game->grid);
  DrawText(TextFormat("%d", game->score), window_size.x - 69, 20, 69, BLACK);
}
