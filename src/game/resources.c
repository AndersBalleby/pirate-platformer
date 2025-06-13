#include "resources.h"
#include <raylib.h>
#include <stdio.h>

ResourceManager_t *initResourceManager() {
  ResourceManager_t *rs_manager =
      (ResourceManager_t *)malloc(sizeof(ResourceManager_t));
  if (rs_manager == NULL) {
    printf("Fejl: Kunne ikke initialisere hukommelse til resource manager\n");
    return NULL;
  }
  
  // TODO: Ændre initial_capacity senere
  // Resources
  size_t initial_capacity = 200;
  rs_manager->arr_resources = malloc(initial_capacity * sizeof(Resource_t));
  rs_manager->size_resources = 0;

  // Spritesheet
  rs_manager->arr_spritesheet = malloc(MAX_SPRITESHEET_SIZE * sizeof(Spritesheet_t));
  rs_manager->size_spritesheet = 0;

  return rs_manager;
}

void destroyResourceManager(ResourceManager_t *rs_manager) {
  // Unload resources
  for (size_t i = 0; i < rs_manager->size_resources; ++i) {
    if (rs_manager->arr_resources[i].is_texture_loaded) {
      UnloadTexture(rs_manager->arr_resources[i].texture);
    }
  }


  for(size_t i = 0; i < rs_manager->size_spritesheet; ++i) {
    for(size_t j = 0; j < rs_manager->arr_spritesheet[i].count; ++j) {
      UnloadTexture(rs_manager->arr_spritesheet[i].sliced_images[j]);
    }
  }
  
  free(rs_manager->arr_resources);
  free(rs_manager->arr_spritesheet);
  free(rs_manager);
}

Resource_t *getResource(ResourceManager_t *rs_manager, const char *name) {
  for (size_t i = 0; i < rs_manager->size_resources; ++i) {
    if (strcmp(rs_manager->arr_resources[i].name, name) == 0) {
      return &rs_manager->arr_resources[i];
    }
  }

  return NULL;
}

bool loadResource(ResourceManager_t *rs_manager, const char *name,
                  const char *file_path, bool load_texture) {

  if (!validatePath(file_path)) {
    printf("Fejl: Kunne ikke validere filsti: %s\n", file_path);
    return false;
  }

  if (getResource(rs_manager, name) != NULL) {
    printf("Fejl: Resource eksisterer allerede: %s\n", name);
    return false;
  }

  Resource_t resource = {.name = name,
                         .file_path = file_path,
                         .is_texture_loaded = false,
                         .texture = 0};

  if (load_texture) {
    Texture2D texture = LoadTexture(file_path);
    if (texture.id == 0) {
      printf("Fejl: Kunne ikke indlæse texture %s fra %s\n", name, file_path);
      return false;
    }
    resource.texture = texture;
    resource.is_texture_loaded = true;
  }

  rs_manager->arr_resources[rs_manager->size_resources++] = resource;

  return true;
}


bool loadSpritesheet(ResourceManager_t *rs_manager, const char *name,
                     const char *file_path) {
  if (!validatePath(file_path)) {
    printf("Fejl: Kunne ikke validere filsti: %s\n", file_path);
    return false;
  }

  if (getSpritesheet(rs_manager, name) != NULL) {
    printf("Fejl: Spritesheet med navn '%s' eksisterer allerede\n", name);
    return false;
  }

  Texture2D *sliced_images =
      (Texture2D *)malloc(sizeof(Texture2D) * MAX_SLICED_TEXTURES);
  if (sliced_images == NULL) {
    printf("Fejl: Kunne ikke allokere hukommelse til spritesheet: %s\n", name);
    return false;
  }

  // Begynd at indlæse billeder fra spritesheet
  size_t image_count = 0;
  Image spritesheet_image = LoadImage(file_path);
  for (int i = 0; i < spritesheet_image.height / TILE_SIZE; ++i) {
    for (int j = 0; j < spritesheet_image.width / TILE_SIZE; ++j) {

      // Beregn position af tile på spritesheet billede
      Rectangle tile_rect = (Rectangle){.x = j * TILE_SIZE,
                                        .y = i * TILE_SIZE,
                                        .width = TILE_SIZE,
                                        .height = TILE_SIZE};

      Image tile_image = ImageFromImage(spritesheet_image, tile_rect);
      Texture2D tile_texture = LoadTextureFromImage(tile_image);

      sliced_images[image_count++] = tile_texture;
      UnloadImage(tile_image);
    }
  }

  UnloadImage(spritesheet_image);

  if (sliced_images == NULL || image_count == 0) {
    printf("Fejl: Der er ikke indlæst nogen billeder fra spritesheet: %s\n",
           name);
    return false;
  }
  
  // Tilføj spritesheet til resource manager
  rs_manager->arr_spritesheet[rs_manager->size_spritesheet++] =
      (Spritesheet_t){.name = name, .sliced_images = sliced_images, .count = image_count};

  return true;
}

Spritesheet_t *getSpritesheet(ResourceManager_t *rs_manager, const char *name) {
  for(size_t i = 0; i < rs_manager->size_spritesheet; ++i) {
    if(strcmp(rs_manager->arr_spritesheet[i].name, name) == 0) {
      return &rs_manager->arr_spritesheet[i];
    }
  }
  return NULL;
}

