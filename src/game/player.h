#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define TEXTURE_PATH "../resources/character/idle/1.png"

typedef struct {
  Texture texture;
  Vector2 position;
  float speed;
} Player;

Player createPlayer();

void update(Player* player);
void drawPlayer(Player *player);
void destroyPlayer(Player *player); // free memory
