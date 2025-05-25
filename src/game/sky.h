#pragma once

#include "raylib.h"

#define SKY_BOTTOM_PATH "resources/decoration/sky/sky_bottom.png"
#define SKY_MIDDLE_PATH "resources/decoration/sky/sky_middle.png"
#define SKY_TOP_PATH "resources/decoration/sky/sky_top.png"

typedef struct Sky {
  Texture2D bottom;
  Texture2D middle;
  Texture2D top;
} Sky;

Sky initSky();
void drawSky(Sky *sky);
void destroySky(Sky *sky);
