#include "player.h"
#include <raylib.h>

Player createPlayer() { // Refactor senere
  Image player_image = LoadImage(TEXTURE_PATH);
  Texture2D texture = LoadTextureFromImage(player_image); 
  
  ImageFlipHorizontal(&player_image);
  Texture2D rev_image = LoadTextureFromImage(player_image);

  Vector2 spawn_pos = getSpawnPos();
  Rectangle collision_rect =
      (Rectangle){spawn_pos.x, spawn_pos.y, texture.width, texture.height};

  UnloadImage(player_image);

  return (Player){
      .display_texture = texture,
      .texture = texture,
      .rev_texture = rev_image,
      .position = spawn_pos,
      .direction = (Vector2){0, 0},
      .collision_rect = collision_rect,
      .speed = PLAYER_SPEED,
      .on_ground = false,
      .last_jump_time = 0.0,
      .gravity = GRAVITY,
      .state = PLAYER_STATE_IDLE,
  };
}

void updatePlayer(Player *player) {
  getInput(player);
  updatePlayerState(player);

  player->position.x = player->collision_rect.x;
  player->position.y = player->collision_rect.y;
}

void getInput(Player *player) {
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    player->direction.x = -1;
    player->display_texture = player->rev_texture;
  } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    player->direction.x = 1;
    player->display_texture = player->texture;
  } else {
    player->direction.x = 0;
  }

  if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) &&
      player->on_ground) {
    jump(player);
  }
}

void updatePlayerState(Player *player) {
  if (!(player->on_ground) && player->direction.y > 0) {
    player->state = PLAYER_STATE_FALLING;
    return;
  } else if (!(player->on_ground) && player->direction.y < 0) {
    player->state = PLAYER_STATE_JUMPING;
    return;
  }

  if (player->direction.x == 0) {
    player->state = PLAYER_STATE_IDLE;
  } else if (player->direction.x > 0 || player->direction.x < 0) {
    player->state = PLAYER_STATE_RUNNING;
  }
}

void animate(Player *player) {}

void jump(Player *player) { player->direction.y = JUMP_SPEED; }

void applyGravity(Player *player) {
  player->direction.y += player->gravity;
  player->collision_rect.y += player->direction.y;
}

void drawPlayer(Player *player, Vector2 offset) {
  Vector2 screenPos = {player->position.x - offset.x,
                       player->position.y - offset.y};

  DrawTexture(player->display_texture, (int)screenPos.x, (int)screenPos.y, WHITE);

  /* Collision Box

  DrawTextureV(player->texture, player->position, WHITE);
  DrawRectangleLines(
    (int)player->collision_rect.x,
    (int)player->collision_rect.y,
    (int)player->collision_rect.width,
    (int)player->collision_rect.height,
    RED
    );

*/
}

Vector2 getSpawnPos() {
  int map[ROWS][COLS];
  if (readCSVToMap("levels/0/level_0_player.csv", ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if (value == 0) {
          return (Vector2){j * TILE_SIZE, i * TILE_SIZE};
        }
      }
    }
  }

  return (Vector2){0, 0};
}

void destroyPlayer(Player *player) { 
  UnloadTexture(player->texture); 
  UnloadTexture(player->rev_texture);
}
