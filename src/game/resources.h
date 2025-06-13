#pragma once

#include "../utils/utils.h"
#include "raylib.h"

#include <stdlib.h>

#define MAX_SPRITESHEET_SIZE 3
#define MAX_SLICED_TEXTURES 16
#define TILE_SIZE 64
/*
  *
  *     NY RESOURCE MANAGER
  *
  *
  *
  *
*/

typedef struct Resource {
  const char *name;
  const char *file_path;
  bool is_texture_loaded;
  Texture2D texture;
} Resource_t;

typedef struct Spritesheet {
  const char *name;
  Texture2D *sliced_images;
  size_t count;
} Spritesheet_t;

typedef struct ResourceManager {
  Resource_t *arr_resources;
  size_t size_resources;

  Spritesheet_t *arr_spritesheet;
  size_t size_spritesheet;
} ResourceManager_t;

// -- ResourceManager
ResourceManager_t *initResourceManager();
void destroyResourceManager(ResourceManager_t *rs_manager);

// -- Resources
bool loadResource(ResourceManager_t *rs_manager, const char *name, const char *file_path, bool load_texture);
// Resource_t loadResourceFromImage(); -- måske lave dette senere?
Resource_t *getResource(ResourceManager_t *rs_manager, const char *name);

// -- Spritesheets
bool loadSpritesheet(ResourceManager_t *rs_manager, const char *name, const char *file_path);
Spritesheet_t *getSpritesheet(ResourceManager_t *rs_manager, const char *name);

