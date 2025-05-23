#pragma once

#include "map.h"
#include "player.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

#define CAMERA_X 300
#define CAMERA_Y 350
#define CAMERA_WIDTH 350
#define CAMERA_HEIGHT 200

typedef struct P_Camera {
  Rectangle rect;
  Vector2 offset;
} P_Camera;

P_Camera initCamera();
void boxTargetCamera(P_Camera *camera, Player *player);
void customDraw(P_Camera *camera, Tile *tiles_arr, size_t tiles_size, Player *player);
