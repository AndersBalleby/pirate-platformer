#pragma once
#include <stdio.h>

#include "game/map.h"
#include "game/player.h"

typedef struct Game {
    Player player;
    Map map;
} Game;

Game createGame();
void runGame(Game *game);
void stopGame(Game *game);