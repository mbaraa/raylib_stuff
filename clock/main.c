#include "src/analog_clock.h"
#include <raylib.h>

const int window_width = 690;
const int window_height = 690;

int main(void) {
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_width, window_height, "Clock");
  SetTargetFPS(60);

  AnalogClock *clock =
      analog_clock_create(300, (Vector2){.x = (float)window_width / 2,
                                         .y = (float)window_height / 2});

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    analog_clock_draw(clock);

    EndDrawing();
  }

  analog_clock_destroy(clock);
  CloseWindow();

  return 0;
}
