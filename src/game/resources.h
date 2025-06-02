#pragma once

#include "../utils/utils.h"
#include "raylib.h"

#include <stdlib.h>

#define MAX_SLICED_TEXTURES 16
#define TILE_SIZE 64

#define CRATE_TILE_PATH "resources/terrain/crate.png"


typedef struct Spritesheet {
  Texture2D *sliced_images;
  size_t count;
} Spritesheet;

typedef struct Resources {
  Spritesheet terrain_spritesheet;
  Spritesheet player_setup_spritesheet;
  Texture2D *crate_texture;
} Resources;


Resources loadResources();
Spritesheet loadSpritesheet(const char *tiles_image);
void unloadSpritesheet(Spritesheet *spritesheet);
void destroyResources(Resources *resources);
