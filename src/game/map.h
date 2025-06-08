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

/* SPRITESHEETS */
#define PATH_TERRAIN_SPRITESHEET "resources/terrain/terrain_tiles.png"
#define PATH_PLAYER_SETUP_SPRITESHEET "resources/character/setup_tiles.png"
#define PATH_COIN_SPRITESHEET "resources/coins/coin_tiles.png"
#define PATH_GRASS_SPRITESHEET "resources/decoration/grass/grass.png"

/* CSV FILES */
#define PATH_TERRAIN_CSV "levels/0/level_0_terrain.csv"
#define PATH_CRATE_CSV "levels/0/level_0_crates.csv"
#define PATH_COIN_CSV "levels/0/level_0_coins.csv"
#define PATH_GRASS_CSV "levels/0/level_0_grass.csv"
#define PATH_BG_PALM_CSV "levels/0/level_0_bg_palms.csv"
#define PATH_FG_PALM_CSV "levels/0/level_0_fg_palms.csv"

/* SINGLE TEXTURES */
#define PATH_CRATE_IMAGE "resources/terrain/crate.png"
#define PATH_BG_PALM_IMAGE "resources/terrain/palm_bg/bg_palm_1.png"
#define PATH_FG_PALM_LARGE_IMAGE "resources/terrain/palm_large/large_1.png"
#define PATH_FG_PALM_SMALL_IMAGE "resources/terrain/palm_small/small_1.png"

typedef enum TileAttribute {
  ATTRIBUTE_COLLIDEABLE,
  ATTRIBUTE_DECORATION,
  ATTRIBUTE_INVISIBLE,
  ATTRIBUTE_ANIMATED
} TileAttribute;

typedef enum TileType {
  TYPE_TILE_TERRAIN,
  TYPE_TILE_PLAYER_SETUP,
  TYPE_TILE_CRATE,
  TYPE_TILE_COIN,
  TYPE_TILE_GRASS,
  TYPE_TILE_BG_PALM,
  TYPE_TILE_FG_PALM_LARGE,
  TYPE_TILE_FG_PALM_SMALL
} TileType;

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
  ResourceManager_t *rs_manager;
} Map;

Map createMap(int level_id, ResourceManager_t *rs_manager);
void insertTiles(TileGroup *group, Tile *tile_arr, size_t *size_ptr);
void destroyMap(Map *map);
void updateMap(Map *map);
