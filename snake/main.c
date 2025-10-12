#include "./src/food.h"
#include "./src/grid.h"
#include "./src/snake.h"
#include "src/game.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  Grid *grid = grid_create(20, 42, DARKGREEN);
  Position window_size = grid_get_window_size(grid);

  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_size.x, window_size.y, "Snake!");
  SetTargetFPS(60);

  Game *game = game_new(
      grid,
      (GameConfig){
          .speed = 1,
          .snake_head_cell = (Cell){.color = DARKPURPLE, .roundness = 0.6},
          .snake_body_cell = (Cell){.color = PURPLE, .roundness = 0.2},
          .snake_inital_position =
              (Position){
                  .x = grid->cells_count_sqrt / 2,
                  .y = grid->cells_count_sqrt / 2,
              },
          .food_color = RED,
      });

  while (!WindowShouldClose()) {
    game_update(game);
    BeginDrawing();

    ClearBackground(DARKGREEN);
    game_draw(game);

    EndDrawing();

    /* usleep(1000000 / 60); */
  }

  grid_destroy(grid);
  game_destroy(game);
  CloseWindow();

  return 0;
}
