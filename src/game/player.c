#include "player.h"

Player createPlayer() {
  return (Player) {
    .texture = LoadTexture(TEXTURE_PATH),
    .position = (Vector2) {0, 0},
    .speed = 5.0f
  };
}

void update(Player *player) {
  if (player->position.x + 64>= GetScreenWidth()) {
    player->speed = 0;
  } else if (player->position.x <= 0) {
    player->speed = 5;
  }

  player->position.x += player->speed;
}

void drawPlayer(Player *player) {
  DrawTextureV(player->texture, player->position, WHITE);
}

void destroyPlayer(Player *player) {
  UnloadTexture(player->texture);
}
