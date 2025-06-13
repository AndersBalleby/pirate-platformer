// Decoration indeholder sky, water og clouds

#pragma once

#include "map.h"
#include "raylib.h"

/* WATER */
#define WATER_SPEED 0.12f
#define WATER_PATH_1 "resources/decoration/water/1.png"
#define WATER_PATH_2 "resources/decoration/water/2.png"
#define WATER_PATH_3 "resources/decoration/water/3.png"
#define WATER_PATH_4 "resources/decoration/water/4.png"

typedef struct Water {
  Texture2D water_tiles[4];
  float anim_index;
} Water_t;

Water_t initWater();
void animateWater(Water_t *water);
void drawWater(Water_t *water, Vector2 offset);
void destroyWater(Water_t *water);

/* SKY */
#define SKY_BOTTOM_PATH "resources/decoration/sky/sky_bottom.png"
#define SKY_MIDDLE_PATH "resources/decoration/sky/sky_middle.png"
#define SKY_TOP_PATH "resources/decoration/sky/sky_top.png"

typedef struct Sky {
  Texture2D bottom;
  Texture2D middle;
  Texture2D top;
} Sky_t;

Sky_t initSky();
void drawSky(Sky_t *sky);
void destroySky(Sky_t *sky);
