#include "resources.h"
#include "map.h"
#include <raylib.h>

Resources loadResources() {

  Texture2D *crate_texture = (Texture2D *) malloc(sizeof(Texture2D));
  *crate_texture = LoadTexture(CRATE_TILE_PATH);

  return (Resources){
      .terrain_spritesheet = loadSpritesheet(TERRAIN_SPRITESHEET),
      .player_setup_spritesheet = loadSpritesheet(PLAYER_SETUP_SPRITESHEET),
      .crate_texture = crate_texture};
}

Spritesheet loadSpritesheet(const char *tiles_image) {
  if (!validatePath(tiles_image)) {
    perror("ugyldig tile image path");
    return (Spritesheet){.sliced_images = NULL, .count = 0};
  }

  Texture2D *sliced_images = malloc(sizeof(Texture2D) * MAX_SLICED_TEXTURES);
  size_t image_count = 0;
  Image tile_image = LoadImage(tiles_image);

  for (int i = 0; i < tile_image.height / TILE_SIZE; ++i) {
    for (int j = 0; j < tile_image.width / TILE_SIZE; ++j) {
      Image sliced_image =
          ImageFromImage(tile_image, (Rectangle){.x = j * TILE_SIZE,
                                                 .y = i * TILE_SIZE,
                                                 .width = TILE_SIZE,
                                                 .height = TILE_SIZE});

      Texture2D sliced_texture = LoadTextureFromImage(sliced_image);
      sliced_images[image_count] = sliced_texture;

      ++image_count;
      UnloadImage(sliced_image);
    }
  }

  UnloadImage(tile_image);
  if (sliced_images == NULL || image_count == 0) {
    perror("images er NULL eller image count er 0");
    return (Spritesheet){.sliced_images = NULL, .count = 0};
  }

  return (Spritesheet){.sliced_images = sliced_images, .count = image_count};
}

void unloadSpritesheet(Spritesheet *spritesheet) {
  for (size_t i = 0; i < spritesheet->count; ++i) {
    UnloadTexture(spritesheet->sliced_images[i]);
  }

  free(spritesheet->sliced_images);
}

void destroyResources(Resources *resources) {
  unloadSpritesheet(&resources->terrain_spritesheet);
  unloadSpritesheet(&resources->player_setup_spritesheet);
  UnloadTexture(*resources->crate_texture);
  free(resources->crate_texture);
}
