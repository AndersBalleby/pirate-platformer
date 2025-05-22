#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define TEXTURE_PATH "resources/character/idle/1.png"
#define JUMP_COOLDOWN 0.20f
#define JUMP_SPEED    -16
#define GRAVITY       0.8f
#define PLAYER_SPEED  8.0f

typedef struct {
  Texture texture;
  Vector2 position;
  Vector2 direction;
  Rectangle collision_rect;
  float speed;
  bool on_ground;
  float last_jump_time;
  float gravity;
} Player;

Player createPlayer(Vector2 spawn_pos);

void updatePlayer(Player* player);
void drawPlayer(Player *player);
void destroyPlayer(Player *player); // free memory
void getInput(Player *player);
void jump(Player *player);
void applyGravity(Player *player);