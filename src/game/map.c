#include "map.h"

Map createMap(int level_id) {
  Tile *tiles_arr = (Tile*) malloc(sizeof(Tile) * MAX_TILES);
  if(tiles_arr == NULL) {
    return (Map) { .tiles_arr = NULL, .arr_size = 0};
  }

  size_t tiles_size = 0;
  int map[ROWS][COLS];

  if(readCSVToMap("levels/0/level_0_terrain.csv", ROWS, COLS, map)) {
    for(int i = 0; i < ROWS; ++i) {
      for(int j = 0; j < COLS; ++j) {

        if(map[i][j] != -1) {
          tiles_arr[tiles_size] = (Tile) {
            .texture = LoadTexture("resources/terrain/crate.png"),
            .position = (Vector2) {j * TILE_SIZE, i * TILE_SIZE},
          };

          ++tiles_size;
        }
      }
    }
  }

  return (Map) {
    .tiles_arr = tiles_arr,
    .arr_size = tiles_size
  };
}

void destroyMap(Map *map) {
  // unload textures
  for(size_t i = 0; i < map->arr_size; ++i) {
    UnloadTexture(map->tiles_arr[i].texture);
  }

  // free pointers
  free(map->tiles_arr);
}