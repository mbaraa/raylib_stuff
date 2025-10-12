#ifndef _CLOCK_H
#define _CLOCK_H

#include <raylib.h>

typedef struct AnalogClock {
  Vector2 position;
  int size;
} AnalogClock;

AnalogClock *analog_clock_create(int size, Vector2 position);
void analog_clock_destroy(AnalogClock *clock);
void analog_clock_draw(AnalogClock *clock);

#endif
