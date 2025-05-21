#include "map.h"

Tile createTile(Texture2D *texture, Vector2 position) {
  return (Tile) {
    .texture = texture,
    .position = position,
    .collision_rect = (Rectangle) {.x = position.x, .y = position.y, .width = texture->width, .height = texture->height}
  };
}

Map createMap(int level_id) {
  Tile *tiles_arr = (Tile*) malloc(sizeof(Tile) * MAX_TILES);
  if(tiles_arr == NULL) {
    return (Map) { .tiles_arr = NULL, .arr_size = 0};
  }

  size_t tiles_size = 0;
  int map[ROWS][COLS];

  Spritesheet terrain_spritesheet = loadSpritesheet("resources/terrain/terrain_tiles.png");
  if (terrain_spritesheet.sliced_images == NULL || terrain_spritesheet.count == 0) {
    perror("kunne ikke indlæse spritesheet fra terrain tiles");
    return (Map) { .tiles_arr = NULL, .arr_size = 0};
  }

  if(readCSVToMap("levels/0/level_0_terrain.csv", ROWS, COLS, map)) {
    for(int i = 0; i < ROWS; ++i) {
      for(int j = 0; j < COLS; ++j) {
        
        int value = map[i][j];
        if(value != -1) {

          tiles_arr[tiles_size] = createTile(
            &terrain_spritesheet.sliced_images[value],
            (Vector2) {j * TILE_SIZE, i * TILE_SIZE}
          );

          ++tiles_size;
        }
      }
    }
  }
  
  return (Map) {
    .tiles_arr = tiles_arr,
    .arr_size = tiles_size,
    .resources = (Resources) {terrain_spritesheet},
  };
}

void updateTile(Tile *tile) {

}

void drawTile(Tile *tile) {
  DrawTextureV(*(tile->texture), tile->position, WHITE);
}

// Update tiles
void updateMap(Map *map) {
  for(size_t i = 0; i < map->arr_size; ++i) {
    updateTile(&map->tiles_arr[i]);
  }
}

void drawMap(Map *map) {
  for(size_t i = 0; i < map->arr_size; ++i) {
    drawTile(&map->tiles_arr[i]);
  }
}

void destroyMap(Map *map) {
  destroyResources(&map->resources);

  free(map->tiles_arr);
}