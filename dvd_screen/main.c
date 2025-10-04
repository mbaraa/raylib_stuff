#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

const float window_height = 420.0;
const float window_width = 690.0;

static Texture2D images[8];

void load_images() {
  char *image_paths[8] = {
      "assets/dvdlogo-01.png", "assets/dvdlogo-02.png", "assets/dvdlogo-03.png",
      "assets/dvdlogo-04.png", "assets/dvdlogo-05.png", "assets/dvdlogo-06.png",
      "assets/dvdlogo-07.png", "assets/dvdlogo-08.png",
  };
  for (size_t i = 0; i < 8; i++) {
    images[i] = LoadTexture(image_paths[i]);
  }
}

void unload_images() {
  for (size_t i = 0; i < 8; i++) {
    UnloadTexture(images[i]);
  }
}

static int last_image_index = 0;

Texture2D get_next_logo() { return images[last_image_index++ % 8]; }

int main(void) {
  InitWindow(window_width, window_height, "DVD Kurwa");
  SetTargetFPS(60);
  load_images();

  Vector2 logo_pos = {
      .x = window_width / 2.0f,
      .y = window_height / 2.0f,
  };
  Vector2 new_logo_pos;

  Texture2D current_logo = get_next_logo();

  float x_increment = 2.0f;
  float y_increment = 2.0f;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    new_logo_pos =
        (Vector2){.x = logo_pos.x + x_increment, .y = logo_pos.y + y_increment};

    if (current_logo.width + new_logo_pos.x >= window_width ||
        new_logo_pos.x <= 0) {
      current_logo = get_next_logo();
      x_increment *= -1.0f;
    }
    if (current_logo.height + new_logo_pos.y >= window_height ||
        new_logo_pos.y <= 0) {
      current_logo = get_next_logo();
      y_increment *= -1.0f;
    }

    logo_pos =
        (Vector2){.x = logo_pos.x + x_increment, .y = logo_pos.y + y_increment};

    DrawTextureV(current_logo, logo_pos, WHITE);

    EndDrawing();
    usleep(1000000 / 60);
  }

  CloseWindow();
  unload_images();

  return 0;
}
