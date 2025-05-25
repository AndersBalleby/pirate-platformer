#pragma once

#include "raylib.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include <stdio.h>

#define TEXTURE_PATH "resources/character/idle/1.png"

// -- PLAYER STATS -- //
#define JUMP_COOLDOWN 0.20f
#define JUMP_SPEED    -16
#define GRAVITY       0.8f
#define PLAYER_SPEED  8.0f


// -- ANIMATIONS -- //
#define ANIMATION_SPEED 0.15

#define ROWS 11
#define COLS 60
#define TILE_SIZE 64

typedef enum PlayerState {
  PLAYER_STATE_IDLE,
  PLAYER_STATE_RUNNING,
  PLAYER_STATE_FALLING,
  PLAYER_STATE_JUMPING
} PlayerState; 

typedef struct PlayerAnimations {
  Texture2D idle_animations[5];
  Texture2D fall_animations[1];
  Texture2D jump_animations[3];
  Texture2D run_animations[6];
} PlayerAnimations;


typedef struct {
  Texture texture;
  Vector2 position;
  Vector2 direction;
  Rectangle collision_rect;
  float speed;
  float animation_frame;
  bool on_ground;
  bool on_ceiling;
  bool on_right;
  float last_jump_time;
  float gravity;
  PlayerState state;
  PlayerAnimations *animations;
} Player;

Player createPlayer();
Vector2 getSpawnPos();

// Update & Draw
void updatePlayer(Player* player);
void drawPlayer(Player *player, Vector2 offset);

// Input & physics
void getInput(Player *player);
void jump(Player *player);
void applyGravity(Player *player);

// Animation
PlayerAnimations *loadPlayerAnimations();
void animate(Player *player);
void checkFrames(Player *player, int max_frames);

// Player state
void updatePlayerState(Player *player);

// Cleanup
void destroyPlayer(Player *player); 

