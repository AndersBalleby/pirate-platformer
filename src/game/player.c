#include "player.h"

Player *createPlayer() {
  Player *player = (Player *)malloc(sizeof(Player));

  player->texture = LoadTexture(TEXTURE_PATH);
  player->position = (Vector2){0, 0};
  player->speed = 5.0f;

  return player;
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
  printf("Deallocating player\n");
  UnloadTexture(player->texture);
  free(player);
}
