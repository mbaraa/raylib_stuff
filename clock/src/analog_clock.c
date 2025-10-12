#include "analog_clock.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

AnalogClock *analog_clock_create(int size, Vector2 position) {
  AnalogClock *clock = (AnalogClock *)malloc(sizeof(AnalogClock));
  clock->position = position;
  clock->size = size;

  return clock;
}

void analog_clock_destroy(AnalogClock *clock) {
  free(clock);
  clock = NULL;
}

void analog_clock_draw_face(AnalogClock *clock) {
  DrawCircle(clock->position.x, clock->position.y, clock->size, DARKGRAY);
  DrawCircle(clock->position.x, clock->position.y,
             clock->size - (int)((float)clock->size * 0.05), LIGHTGRAY);
}

void analog_clock_draw_hour_markers(AnalogClock *clock) {
  Rectangle rect = {
      .x = clock->position.x,
      .y = clock->position.y,
      .width = (int)((float)clock->size * 0.025),
      .height = clock->size,
  };
  for (size_t i = 0; i < 12; i++) {
    DrawRectanglePro(rect, (Vector2){.x = rect.width / 2, .y = rect.height},
                     i * 30, DARKGRAY);
  }
  DrawCircle(clock->position.x, clock->position.y, clock->size - 50, LIGHTGRAY);
}

void analog_clock_draw_hand(AnalogClock *clock, float width, float height,
                            int angle, Color color) {
  Rectangle rect = {
      .x = clock->position.x,
      .y = clock->position.y,
      .width = width,
      .height = height,
  };
  DrawRectanglePro(rect, (Vector2){.x = width / 2, .y = height}, angle, BLACK);
}

void analog_clock_draw_hands(AnalogClock *clock) {
  time_t time_secs = time(NULL);
  struct tm *current_time = localtime(&time_secs);
  float hand_width = (float)clock->size * 0.03;

  analog_clock_draw_hand(clock, hand_width,
                         clock->size - (int)((float)clock->size * 0.2),
                         (float)current_time->tm_sec * 6.0f, BLACK);
  analog_clock_draw_hand(clock, hand_width,
                         clock->size - (int)((float)clock->size * 0.4),
                         (float)current_time->tm_min * 6.0f +
                             (((float)current_time->tm_sec / 60) * 6),
                         BLACK);
  analog_clock_draw_hand(clock, hand_width,
                         clock->size - (int)((float)clock->size * 0.5),
                         (float)(current_time->tm_hour % 12) * 30.0f +
                             (((float)current_time->tm_min / 60) * 30),
                         BLACK);
}

void analog_clock_draw(AnalogClock *clock) {
  analog_clock_draw_face(clock);
  analog_clock_draw_hour_markers(clock);
  analog_clock_draw_hands(clock);
  DrawCircle(clock->position.x, clock->position.y, 5, RED);
}
