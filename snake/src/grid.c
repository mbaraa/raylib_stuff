#include "./grid.h"
#include "./utils.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Grid *grid_create(int cell_size, int cells_count_sqrt, Color empty_cell_color) {
  Grid *grid = (Grid *)malloc(sizeof(Grid));
  grid->cell_size = cell_size;
  grid->cells = (Cell **)malloc(sizeof(Cell *) * cells_count_sqrt);
  grid->cells_count_sqrt = cells_count_sqrt;
  grid->empty_cell_color = empty_cell_color;
  for (int i = 0; i < cells_count_sqrt; i++) {
    grid->cells[i] = (Cell *)malloc(sizeof(Cell) * cells_count_sqrt);
    for (int j = 0; j < cells_count_sqrt; j++) {
      grid->cells[i][j] = (Cell){
          .color = empty_cell_color,
      };
    }
  }

  return grid;
}

void grid_destroy(Grid *grid) {
  for (int i = 0; i < grid->cells_count_sqrt; i++) {
    free(grid->cells[i]);
    grid->cells[i] = NULL;
  }
  free(grid->cells);
  grid->cells = NULL;

  free(grid);
  grid = NULL;
}

void grid_reset(Grid *grid) {
  for (int i = 0; i < grid->cells_count_sqrt; i++) {
    for (int j = 0; j < grid->cells_count_sqrt; j++) {
      grid->cells[i][j].color = grid->empty_cell_color;
    }
  }
}

Position grid_get_window_size(Grid *grid) {
  return (Position){
      .x = (float)grid->cell_size * grid->cells_count_sqrt,
      .y = (float)grid->cell_size * grid->cells_count_sqrt,
  };
}

void grid_draw(Grid *grid) {
  for (int i = 0; i < grid->cells_count_sqrt; i++) {
    for (int j = 0; j < grid->cells_count_sqrt; j++) {
      Rectangle rect = {
          .x = j * grid->cell_size,
          .y = i * grid->cell_size,
          .width = grid->cell_size,
          .height = grid->cell_size,
      };
      DrawRectangleRounded(rect, grid->cells[i][j].roundness, 10,
                           grid->cells[i][j].color);
    }
  }
}

bool grid_check_position(Grid *grid, Position position) {
  return position.x < grid->cells_count_sqrt && position.x >= 0 &&
         position.y < grid->cells_count_sqrt && position.y >= 0;
}

void grid_fill_cell(Grid *grid, Position position, Cell cell) {
  if (!grid_check_position(grid, position)) {
    return;
  }

  grid->cells[position.y][position.x] = cell;
}

bool grid_is_cell_empty(Grid *grid, Position position) {
  return grid_check_position(grid, position) &&
         compare_colors(grid->cells[position.y][position.x].color,
                        grid->empty_cell_color);
}

Color grid_get_cell_color(Grid *grid, Position position) {
  if (!grid_check_position(grid, position)) {
    return grid->empty_cell_color;
  }

  return grid->cells[position.y][position.x].color;
}
