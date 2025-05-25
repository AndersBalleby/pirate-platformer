#pragma once
#include <stdio.h>

#include "../utils/utils.h"
#include "camera.h"
#include "map.h"
#include "player.h"
#include "sky.h"

typedef struct Game {
  Player player;
  Map map;
  P_Camera camera;
  Sky sky;
} Game;

void horizontalMovementCollision(Game *game);
void verticalMovementCollision(Game *game);

Game createGame();
void runGame(Game *game);
void stopGame(Game *game);
void drawMap(P_Camera *camera, Player *player, Map *map);

Player *getPlayer(Game *game);
