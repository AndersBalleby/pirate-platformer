#include "map.h"

Tile *createTile(const char *image_path, Vector2 position, bool load_texture) {
  Tile *tile = (Tile *)malloc(sizeof(Tile));

  // Tjek tile memory
  if (tile == NULL) {
    perror("malloc fejlede");
    return NULL;
  }

  if (!load_texture) { // Manuel tjek om det er en valid image_path

    // Filen eksisterer
    if (access(image_path, F_OK) == 0) {
      // Copy image path
      strncpy(tile->image_path, image_path, sizeof(tile->image_path) - 1);
      tile->image_path[sizeof(tile->image_path) - 1] = '\0';

      tile->position = position;
    } else {
      free(tile);
      return NULL; // Kunne ikke validere path
    }

  } else { // Lad Raylib loade texturen
    Texture2D testText = LoadTexture(image_path);
    if (testText.id == 0) {
      free(tile);
      return NULL;
    }

    tile->texture = testText;
    // Copy image path
    strncpy(tile->image_path, image_path, sizeof(tile->image_path) - 1);
    tile->image_path[sizeof(tile->image_path) - 1] = '\0';

    tile->position = position;
  }

  return tile;
}

#define ROWS 11
#define COLS 60
#define TILE_SIZE 64

bool generateMap(int level_id) {

  char path[128];

  snprintf(path, sizeof(path), "../levels/%d/level_%d_crates.csv", level_id,
           level_id);

  if (!validatePath(path))
    return false;

  int map[ROWS][COLS];
  char *endptr;
  if (readCSVToMap(path, ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if (value != -1) {
          Vector2 position = (Vector2){j * TILE_SIZE, i * TILE_SIZE};
          createTile("../resources/terrain/crate.png", position, false);
        }
      }
    }
  }

  return true;
}
