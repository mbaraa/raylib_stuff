#include "./src/food.h"
#include "./src/grid.h"
#include "./src/snake.h"

#include <raylib.h>
#include <stdbool.h>
#include <unistd.h>

int main(void) {
  Grid *grid = grid_create(20, 42, DARKGREEN);
  Position window_size = grid_get_window_size(grid);

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
    snake_update_position(snake);
    if (snake->head->position.x == apple_position.x &&
        snake->head->position.y == apple_position.y) {
      apple_position = place_food(grid);
      snake_grow(snake);
      score++;
    }
    snake_update_position_key(snake);
    grid_reset(grid);

    BeginDrawing();

    ClearBackground(BLACK);
    grid_fill_cell(grid, apple_position, (Cell){.color = apple_color});
    snake_draw(snake, grid);
    grid_draw(grid);
    DrawText(TextFormat("%d", score), window_size.x - 69, 20, 69, BLACK);

    EndDrawing();

    usleep(1000000 / 60);
  }

  grid_destroy(grid);
  snake_destroy(snake);
  CloseWindow();

  return 0;
}
