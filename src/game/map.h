#pragma once
#include "raylib.h"

#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../utils/utils.h"
#include "resources.h"

#define MAX_TILES 660 // 11 rows * 60 cols
#define ROWS 11
#define COLS 60
#define TILE_SIZE 64

#define TERRAIN_SPRITESHEET "../resources/terrain/terrain_tiles.png"

typedef struct {
  Texture2D *texture;
  Vector2 position;
  Rectangle collision_rect;
} Tile;

Tile createTile(Texture2D *texture, Vector2 position);
void updateTile(Tile *tile);
void drawTile(Tile *tile);

typedef struct {
  Tile *tiles_arr;
  size_t arr_size;
  Resources resources;
} Map;

Map createMap(int level_id);
void destroyMap(Map *map);
void updateMap(Map *map);
void drawMap(Map *map);