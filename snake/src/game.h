#ifndef _GAME_H
#define _GAME_H

#include "grid.h"
#include "snake.h"

typedef struct GameConfig {
  int speed;
  Position snake_inital_position;
  Cell snake_head_cell;
  Cell snake_body_cell;
  Color food_color;
} GameConfig;

typedef struct Game {
  Grid *grid;
  Snake *snake;
  Position last_food_position;
  int score;
  GameConfig config;
} Game;

Game *game_new(Grid *grid, GameConfig config);
void game_destroy(Game *game);
void game_reset(Game *game);
void game_update(Game *game);
void game_draw(Game *game);

#endif
