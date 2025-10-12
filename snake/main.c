#include "./src/food.h"
#include "./src/grid.h"
#include "./src/snake.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

double last_event_at = 0.0f;

bool check_event_triggered(double interval) {
  double current_time = GetTime();
  if (current_time - last_event_at >= interval) {
    last_event_at = current_time;
    return true;
  }
  return false;
}

int main(void) {
  Grid *grid = grid_create(20, 42, DARKGREEN);
  Position window_size = grid_get_window_size(grid);

  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_size.x, window_size.y, "Snake!");
  SetTargetFPS(60);

  const Color snake_head_color = DARKPURPLE;
  const Color snake_body_color = PURPLE;
  const Color apple_color = RED;
  Position apple_position = place_food(grid);

  double game_speed = 0.1;

  Snake *snake = snake_new(
      (Position){
          .x = grid->cells_count_sqrt / 2,
          .y = grid->cells_count_sqrt / 2,
      },
      (Cell){.color = snake_head_color, .roundness = 0.6},
      (Cell){.color = snake_body_color, .roundness = 0.2});

  int score = 0;

  while (!WindowShouldClose()) {
    if (snake->head->position.x == apple_position.x &&
        snake->head->position.y == apple_position.y) {
      apple_position = place_food(grid);
      snake_grow(snake);
      score++;
    }

    if (snake->head->position.x >= grid->cells_count_sqrt ||
        snake->head->position.x < 0 ||
        snake->head->position.y >= grid->cells_count_sqrt ||
        snake->head->position.y < 0) {
      puts("boo");
      break;
    }

    if (check_event_triggered(game_speed)) {
      snake_update_position(snake);
      snake_update_position_key(snake);
    }
    grid_reset(grid);

    BeginDrawing();

    ClearBackground(DARKGREEN);
    grid_fill_cell(grid, apple_position,
                   (Cell){.color = apple_color, .roundness = 0.5});
    snake_draw(snake, grid);
    grid_draw(grid);
    DrawText(TextFormat("%d", score), window_size.x - 69, 20, 69, BLACK);

    EndDrawing();

    /* usleep(1000000 / 60); */
  }

  grid_destroy(grid);
  snake_destroy(snake);
  CloseWindow();

  return 0;
}
