#pragma once
#include "raylib.h"

#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../utils/utils.h"

#define MAXTILES 660 // 11 rows * 60 cols

typedef struct {
  Texture2D texture;
  char image_path[256];
  Vector2 position;
} Tile;

typedef struct {
  Tile tiles_arr[MAXTILES];
} Map;

Tile *createTile(const char *image_path, Vector2 position, bool load_texture);
bool generateMap(int level_id);


