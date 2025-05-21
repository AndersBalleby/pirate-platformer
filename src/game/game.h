#pragma once
#include <stdio.h>

#include "utils/utils.h"
#include "player.h"
#include "map.h"

typedef struct Game {
    Player player;
    Map map;
} Game;


void horizontal_movement_collision(Game *game);
void vertical_movement_collision(Game *game);

Game createGame();
void runGame(Game *game);
void stopGame(Game *game);