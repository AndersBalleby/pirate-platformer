#include "decoration.h"
#include <raylib.h>
#include <sys/types.h>

/* WATER */
Water_t initWater() {
  return (Water_t){
      .water_tiles = {LoadTexture(WATER_PATH_1), LoadTexture(WATER_PATH_2),
                      LoadTexture(WATER_PATH_3), LoadTexture(WATER_PATH_4)},
      .anim_index = 0.0f};
}

void animateWater(Water_t *water) {
  water->anim_index += WATER_SPEED;
  if ((int)water->anim_index >= 4) {
    water->anim_index -= 4;
  }
}

void drawWater(Water_t *water, Vector2 offset) {
  Texture2D texture = water->water_tiles[(int)water->anim_index];
  DrawTexturePro(texture,
                 (Rectangle){0.0f, 0.0f, texture.width, texture.height},
                 (Rectangle){0.0f, offset.y, 1280, (float)100}, (Vector2){0, 0},
                 0.0f, WHITE);
}

void destroyWater(Water_t *water) {
  for (uint i = 0; i < 4; ++i) {
    UnloadTexture(water->water_tiles[i]);
  }
}

/* SKY */
Sky_t initSky() {
  return (Sky_t){.bottom = LoadTexture(SKY_BOTTOM_PATH),
                 .middle = LoadTexture(SKY_MIDDLE_PATH),
                 .top = LoadTexture(SKY_TOP_PATH)};
}

void drawSky(Sky_t *sky) {

  // top
  DrawTexturePro(sky->top,
                 (Rectangle){0.0f, 0.0f, sky->top.width, sky->top.height},
                 (Rectangle){0.0f, 0.0f, 1280, (float)800.0 / 1.25},
                 (Vector2){0, 0}, 0.0f, WHITE);

  // middle
  DrawTexturePro(sky->middle,
                 (Rectangle){0.0f, 0.0f, sky->middle.width, sky->middle.height},
                 (Rectangle){0.0f, (float)800.0 / 1.25, 1280, 100},
                 (Vector2){0, 0}, 0.0f, WHITE);

  // bottom
  DrawTexturePro(sky->bottom,
                 (Rectangle){0.0f, 0.0f, sky->bottom.width, sky->bottom.height},
                 (Rectangle){0.0f, (float)(800.0 / 1.25) + 100, 1280, 800.0},
                 (Vector2){0, 0}, 0.0f, WHITE);
}

void destroySky(Sky_t *sky) {
  UnloadTexture(sky->top);
  UnloadTexture(sky->middle);
  UnloadTexture(sky->bottom);
}
