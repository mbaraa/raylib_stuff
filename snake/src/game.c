#include "./game.h"
#include "food.h"
#include "grid.h"
#include "snake.h"
#include "utils.h"
#include <raylib.h>
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
  game->game_running = true;

  return game;
}

void game_destroy(Game *game) {
  snake_destroy(game->snake);
  UnloadSound(game->config.eat_sound);
  UnloadSound(game->config.wall_hit_sound);
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
  if (!game->game_running) {
    if (IsKeyDown(KEY_ENTER)) {
      game->game_running = true;
      game_reset(game);
    }
    return;
  }

  if (game->snake->head->position.x == game->last_food_position.x &&
      game->snake->head->position.y == game->last_food_position.y) {
    game->last_food_position = place_food(game->grid);
    snake_grow(game->snake);
    game->score++;
    PlaySound(game->config.eat_sound);
  }

  if (game->snake->head->position.x >= game->grid->cells_count_sqrt ||
      game->snake->head->position.x < 0 ||
      game->snake->head->position.y >= game->grid->cells_count_sqrt ||
      game->snake->head->position.y < 0) {
    game->game_running = false;
    PlaySound(game->config.wall_hit_sound);
    return;
  }

  if (compare_colors(
          grid_get_cell_color(game->grid, game->snake->head->position),
          game->snake->tail->cell.color)) {
    game->game_running = false;
    PlaySound(game->config.wall_hit_sound);
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
  if (!game->game_running) {
    DrawText("Game Over", (window_size.x / 2) - 250, window_size.y / 2 - 100,
             100, RED);
    DrawText(TextFormat("Final score: %d", game->score),
             (window_size.x / 2) - 150, window_size.y / 2 + 100 - 100, 42,
             BLACK);
    DrawText("Press 'Enter' to continue!", (window_size.x / 2) - 250,
             window_size.y / 2 + 142 - 100, 42, BLACK);
    return;
  }

  grid_fill_cell(game->grid, game->last_food_position,
                 (Cell){.color = game->config.food_color, .roundness = 0.5});
  snake_draw(game->snake, game->grid);
  grid_draw(game->grid);
  DrawText(TextFormat("%d", game->score), window_size.x - 69, 20, 69, BLACK);
}
