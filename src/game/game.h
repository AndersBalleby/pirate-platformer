#pragma once
#include <stdio.h>

#include "../utils/utils.h"
#include "camera.h"
#include "map.h"
#include "player.h"
#include "resources.h"
#include "decoration.h"

typedef struct Game {
  Player player;
  Map map;
  P_Camera camera;
  Sky_t sky;
  Water_t water;
} Game;

void horizontalMovementCollision(Game *game);
void verticalMovementCollision(Game *game);

Game createGame(ResourceManager_t *rs_manager);
void runGame(Game *game);
void stopGame(Game *game);
void drawMap(Game *game);

Player *getPlayer(Game *game);
