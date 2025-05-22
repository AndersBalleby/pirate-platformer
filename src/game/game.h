#pragma once
#include <stdio.h>

#include "utils/utils.h"
#include "player.h"
#include "map.h"

typedef struct Game {
    Player player;
    Map map;
} Game;

void horizontalMovementCollision(Game *game);
void verticalMovementCollision(Game *game);

Game createGame();
void runGame(Game *game);
void stopGame(Game *game);