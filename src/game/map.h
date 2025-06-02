#pragma once
#include "raylib.h"

#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/utils.h"
#include "resources.h"

#define MAX_TILES 660 // 11 rows * 60 cols
#define ROWS 11
#define COLS 60
#define TILE_SIZE 64

#define TERRAIN_SPRITESHEET "resources/terrain/terrain_tiles.png"
#define PLAYER_SETUP_SPRITESHEET "resources/character/setup_tiles.png"

typedef enum TileAttribute {
  ATTRIBUTE_COLLIDEABLE,
  ATTRIBUTE_DECORATION,
  ATTRIBUTE_INVISIBLE,
  ATTRIBUTE_ANIMATED
} TileAttribute;

typedef enum TileType { TILE_TERRAIN, TILE_PLAYER_SETUP, TILE_CRATE } TileType;

typedef struct {
  Texture2D *texture;
  Vector2 position;
  Rectangle collision_rect;
  TileType tile_type;
  TileAttribute *tile_attributes;
  size_t tile_attribute_size;
} Tile;

typedef struct TileGroup {
  Tile *tiles;
  size_t tiles_size;
} TileGroup;

Tile createTile(Texture2D *texture, TileType type, Vector2 position,
                TileAttribute *tile_attributes, size_t tile_attribute_size);
TileGroup createTileGroup(const char *csv_path, Texture2D *sliced_images,
                          size_t sliced_images_len, Texture2D *single_texture,
                          TileType tile_type);



void updateTile(Tile *tile);
void drawTile(Tile *tile);

typedef struct {
  Tile *tiles_arr;
  size_t arr_size;
  Resources resources;
} Map;

Map createMap(int level_id, Resources resources);
void destroyMap(Map *map);
void updateMap(Map *map);
