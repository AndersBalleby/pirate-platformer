#include "player.h"

Player createPlayer() {
  Texture2D texture = LoadTexture(TEXTURE_PATH);
  Rectangle collision_rect = (Rectangle) {100, 100, texture.width, texture.height};
  return (Player) {
    .texture = texture,
    .position = (Vector2) {100, 100},
    .direction = (Vector2) {0, 0},
    .collision_rect = collision_rect,
    .speed = PLAYER_SPEED,
    .on_ground = false,
    .last_jump_time = 0.0,
    .gravity = GRAVITY
  };
}

void updatePlayer(Player *player) {
  getInput(player);
  player->position.x = player->collision_rect.x;
  player->position.y = player->collision_rect.y;
}

void getInput(Player *player) {
  if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    player->direction.x = -1;
  } else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    player->direction.x = 1;
  } else {
    player->direction.x = 0;
  }

  if(IsKeyPressed(KEY_SPACE) && player->on_ground) {
    jump(player);
  }
}

void jump(Player *player) {
  player->direction.y = JUMP_SPEED;
}

void applyGravity(Player *player) {
  player->direction.y += player->gravity;
  player->collision_rect.y += player->direction.y;
}

void drawPlayer(Player *player) {
  DrawTextureV(player->texture, player->position, WHITE);
  DrawRectangleLines(
    (int)player->collision_rect.x,
    (int)player->collision_rect.y,
    (int)player->collision_rect.width,
    (int)player->collision_rect.height,
    RED
);

}

void destroyPlayer(Player *player) {
  UnloadTexture(player->texture);
}
