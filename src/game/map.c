#include "map.h"

Tile createTile(Texture2D *texture, Vector2 position,
                TileAttribute *tile_attributes, size_t tile_attribute_size) {
  return (Tile){.texture = texture,
                .position = position,
                .collision_rect = (Rectangle){.x = position.x,
                                              .y = position.y,
                                              .width = texture->width,
                                              .height = texture->height},
                .tile_attributes = tile_attributes,
                .tile_attribute_size = tile_attribute_size};
}

Map createMap(int level_id, Resources resources) {
  Tile *tiles_arr = (Tile *)malloc(sizeof(Tile) * MAX_TILES);
  if (tiles_arr == NULL) {
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }

  size_t tiles_size = 0;

  TileGroup terrain_tile_group = createTileGroup(
      "levels/0/level_0_terrain.csv",
      resources.terrain_spritesheet.sliced_images, TILE_TERRAIN);
  TileGroup player_setup_group = createTileGroup(
      "levels/0/level_0_player.csv",
      resources.player_setup_spritesheet.sliced_images, TILE_PLAYER_SETUP);

  for (size_t i = 0; i < terrain_tile_group.tiles_size; ++i) {
    tiles_arr[tiles_size++] = terrain_tile_group.tiles[i];
  }

  for (size_t i = 0; i < player_setup_group.tiles_size; ++i) {
    tiles_arr[tiles_size++] = player_setup_group.tiles[i];
  }

  free(terrain_tile_group.tiles);
  free(player_setup_group.tiles);
  return (Map){
      .tiles_arr = tiles_arr, .arr_size = tiles_size, .resources = resources};
}

TileGroup createTileGroup(const char *csv_path, Texture2D *sliced_images,
                          TileType tile_type) {
  Tile *tile_arr = (Tile *)malloc(sizeof(Tile) * MAX_TILES);
  size_t tiles_size = 0;

  // Map struct
  Texture2D *texture_ptr = NULL;
  Vector2 position = (Vector2){0, 0};
  TileAttribute *attributes = NULL;
  size_t attribute_size = 0;

  int map[ROWS][COLS];
  if (readCSVToMap(csv_path, ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {

        int value = map[i][j];
        if (value != -1) {

          texture_ptr = &sliced_images[value];
          position = (Vector2){j * TILE_SIZE, i * TILE_SIZE};
          switch (tile_type) {
          case TILE_TERRAIN:
            static TileAttribute terrain_attrs[] = {ATTRIBUTE_COLLIDEABLE};
            attributes = terrain_attrs;
            attribute_size = sizeof(terrain_attrs) / sizeof(terrain_attrs[0]);
            break;

          case TILE_PLAYER_SETUP:
            static TileAttribute setup_attrs[] = {ATTRIBUTE_INVISIBLE};
            attributes = setup_attrs;
            attribute_size = sizeof(setup_attrs) / sizeof(setup_attrs[0]);
            break;
          default:
            attributes = NULL;
            attribute_size = 0;
            break;
          }
          tile_arr[tiles_size] =
              createTile(texture_ptr, position, attributes, attribute_size);

          ++tiles_size;
        }
      }
    }
  }

  return (TileGroup){.tiles = tile_arr, .tiles_size = tiles_size};
}

void updateTile(Tile *tile) {}

void drawTile(Tile *tile) {
  for (size_t i = 0; i < tile->tile_attribute_size; ++i) {
    if (tile->tile_attributes[i] == ATTRIBUTE_INVISIBLE)
      return;
  }

  DrawTextureV(*(tile->texture), tile->position, WHITE);
}

// Update tiles
void updateMap(Map *map) {
  for (size_t i = 0; i < map->arr_size; ++i) {
    updateTile(&map->tiles_arr[i]);
  }
}

void destroyMap(Map *map) {
  destroyResources(&map->resources);

  free(map->tiles_arr);
}
