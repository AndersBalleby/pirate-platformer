#include "sky.h"
#include <raylib.h>

Sky initSky() {
  return (Sky){.bottom = LoadTexture(SKY_BOTTOM_PATH),
               .middle = LoadTexture(SKY_MIDDLE_PATH),
               .top = LoadTexture(SKY_TOP_PATH)};
}

void drawSky(Sky *sky) {

  // top
  DrawTexturePro(sky->top,
                 (Rectangle){0.0f, 0.0f, sky->top.width, sky->top.height},
                 (Rectangle){0.0f, 0.0f, 1280, (float)800.0 / 1.25},
                 (Vector2){0, 0}, 0.0f, WHITE);

  // middle
  DrawTexturePro(
      sky->middle,
      (Rectangle){0.0f, 0.0f, sky->middle.width, sky->middle.height},
      (Rectangle){0.0f, (float)800.0 / 1.25, 1280, 100},
      (Vector2){0, 0}, 0.0f, WHITE);

  // bottom
  DrawTexturePro(sky->bottom,
                 (Rectangle){0.0f, 0.0f, sky->bottom.width, sky->bottom.height},
                 (Rectangle){0.0f, (float)(800.0 / 1.25)+100, 1280, 800.0},
                 (Vector2){0, 0}, 0.0f, WHITE);
}

void destroySky(Sky *sky) {
  UnloadTexture(sky->top);
  UnloadTexture(sky->middle);
  UnloadTexture(sky->bottom);
}
