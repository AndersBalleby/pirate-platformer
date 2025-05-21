#pragma once

#include "raylib.h"
#include "utils/utils.h"

#include <stdlib.h>

#define MAX_SLICED_TEXTURES 16
#define TILE_SIZE 64

typedef struct Spritesheet {
    Texture2D *sliced_images;
    size_t count;
} Spritesheet;

typedef struct Resources {
    Spritesheet terrain_spritesheet;
} Resources;


Spritesheet loadSpritesheet(const char *tiles_image);
void unloadSpritesheet(Spritesheet *spritesheet);
void destroyResources(Resources *resources);