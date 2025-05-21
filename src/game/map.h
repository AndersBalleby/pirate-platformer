#pragma once
#include "raylib.h"

#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../utils/utils.h"

#define MAX_TILES 660 // 11 rows * 60 cols
#define ROWS 11
#define COLS 60
#define TILE_SIZE 64

typedef struct {
  Texture2D texture;
  Vector2 position;
} Tile;

typedef struct {
  Tile *tiles_arr;
  size_t arr_size;
} Map;

Map createMap(int level_id);
void destroyMap(Map *map);