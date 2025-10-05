#include "./food.h"
#include "./grid.h"
#include <time.h>

Position place_food(Grid *grid) {
  Position position = {
      .x = GetRandomValue(0, grid->cells_count_sqrt - 1),
      .y = GetRandomValue(0, grid->cells_count_sqrt - 1),
  };

  while (!grid_is_cell_empty(grid, position)) {
    SetRandomSeed(time(NULL));
    position = (Position){
        .x = GetRandomValue(0, grid->cells_count_sqrt - 1),
        .y = GetRandomValue(0, grid->cells_count_sqrt - 1),
    };
  }

  return position;
}
