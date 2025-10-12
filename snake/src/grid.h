#ifndef _GRID_H
#define _GRID_H

#include <raylib.h>
#include <stdbool.h>

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Cell {
  Color color;
  float roundness;
} Cell;

typedef struct Grid {
  int cell_size;
  int cells_count_sqrt;
  Color empty_cell_color;
  Cell **cells;
} Grid;

Grid *grid_create(int cell_size, int cells_count_sqrt, Color empty_cell_color);
void grid_destroy(Grid *grid);
void grid_reset(Grid *grid);
Position grid_get_window_size(Grid *grid);
void grid_draw(Grid *grid);
bool grid_check_position(Grid *grid, Position position);
void grid_fill_cell(Grid *grid, Position position, Cell cell);
bool grid_is_cell_empty(Grid *grid, Position position);
Color grid_get_cell_color(Grid *grid, Position position);

#endif // !_GRID_H
