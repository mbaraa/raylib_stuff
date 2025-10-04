#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const float window_height = 420.0;
const float window_width = 690.0;

typedef struct Ball {
  Vector2 position;
  int speed_x;
  int speed_y;
  float radius;
} Ball;

void ball_draw(Ball *ball) { DrawCircleV(ball->position, ball->radius, WHITE); }

void ball_update_position(Ball *ball) {
  if (ball->position.x + ball->radius >= window_width ||
      ball->position.x - ball->radius <= 0) {
    ball->speed_x *= -1;
  }
  if (ball->position.y + ball->radius >= window_height ||
      ball->position.y - ball->radius <= 0) {
    ball->speed_y *= -1;
  }

  ball->position.x += (float)ball->speed_x;
  ball->position.y += (float)ball->speed_y;
}

void ball_reset(Ball *ball) {
  ball->position.x = window_width / 2.0f;
  ball->position.y = window_height / 2.0f;

  srand(time(NULL));
  ball->speed_x *= pow(-1, rand() % 2);
  ball->speed_y *= pow(-1, rand() % 2);
}

typedef struct Paddle {
  Vector2 position;
  Vector2 size;
  int speed_y;
  int score;
} Paddle;

void paddle_draw(Paddle *paddle) {
  DrawRectangle(paddle->position.x, paddle->position.y, paddle->size.x,
                paddle->size.y, WHITE);
}

void paddle_update_position(Paddle *paddle) {
  if (IsKeyDown(KEY_DOWN) &&
      paddle->position.y + paddle->speed_y + paddle->size.y <= window_height) {
    paddle->position.y += paddle->speed_y;
  }
  if (IsKeyDown(KEY_UP) && paddle->position.y - paddle->speed_y >= 0) {
    paddle->position.y -= paddle->speed_y;
  }
}

void paddle_auto_update_position(Paddle *paddle) {
  srand(time(NULL));
  int move_up = rand() % 2;
  if (move_up % 2 == 1 &&
      paddle->position.y + paddle->speed_y + paddle->size.y <= window_height) {
    paddle->position.y += paddle->speed_y;
  }
  if (move_up % 2 != 1 && paddle->position.y - paddle->speed_y >= 0) {
    paddle->position.y -= paddle->speed_y;
  }
}

Rectangle paddle_rectangle(Paddle *paddle) {
  return (Rectangle){
      .x = paddle->position.x,
      .y = paddle->position.y,
      .width = paddle->size.x,
      .height = paddle->size.y,
  };
}

int ball_check_collision_with_paddle(Ball *ball, Paddle *paddle) {
  if (CheckCollisionCircleRec(ball->position, ball->radius,
                              paddle_rectangle(paddle))) {
    ball->speed_x *= -1;
    ball->speed_y *= -1;
    return 1;
  }

  return 0;
}

int main(void) {
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(window_width, window_height, "Pong!");
  SetTargetFPS(60);

  Ball ball = {
      .position =
          (Vector2){.x = window_width / 2.0f, .y = window_height / 2.0f},
      .radius = 20.0f,
      .speed_x = 5,
      .speed_y = 5,
  };

  const float paddle_x_offset = 5.0f;

  Paddle player_paddle = {
      .position =
          (Vector2){
              .x = window_width - paddle_x_offset - 20.0f /*player's width*/,
              .y = (window_height / 2.0f),
          },
      .size = (Vector2){.x = 20, .y = 120},
      .speed_y = 10,
      .score = 0,
  };

  Paddle computer_paddle = {
      .position =
          (Vector2){
              .x = paddle_x_offset,
              .y = (window_height / 2.0f),
          },
      .size = (Vector2){.x = 20, .y = 120},
      .speed_y = 10,
      .score = 0,
  };

  while (!WindowShouldClose()) {
    BeginDrawing();

    ball_update_position(&ball);
    paddle_update_position(&player_paddle);
    paddle_auto_update_position(&computer_paddle);
    if (ball_check_collision_with_paddle(&ball, &player_paddle)) {
      ball.position.x -= 1;
    }
    if (ball_check_collision_with_paddle(&ball, &computer_paddle)) {
      ball.position.x += 1;
    }
    /* ball_check_collision_with_paddle(&ball, &computer_paddle); */
    if (ball.position.x + ball.radius >= window_width) {
      ball_reset(&ball);
      player_paddle.score++;
    }
    if (ball.position.x - ball.radius <= 0) {
      ball_reset(&ball);
      computer_paddle.score++;
    }

    ClearBackground(BLACK);
    ball_draw(&ball);
    paddle_draw(&player_paddle);
    paddle_draw(&computer_paddle);
    DrawLine(window_width / 2.0f, 0.0f, window_width / 2.0f, window_height,
             WHITE);
    DrawText(TextFormat("%d", player_paddle.score), window_width / 4.0f - 20.0f,
             10.0f, 40, WHITE);
    DrawText(TextFormat("%d", computer_paddle.score),
             3.0 * window_width / 4.0f + 20.0f, 10.0f, 40, WHITE);

    EndDrawing();
    usleep(1000000 / 60);
  }

  CloseWindow();

  return 0;
}
