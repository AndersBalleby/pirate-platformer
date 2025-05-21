#include "game.h"
#include "map.h"
#include "utils/utils.h"

Game createGame() {
  return (Game) {
    .player = createPlayer(),
    .map = createMap(0)
  };
}

void runGame(Game *game) {
  Map map = game->map;
  for(size_t i = 0; i < map.arr_size; ++i) {
    Tile tile = map.tiles_arr[i];
    DrawTextureV(tile.texture, tile.position, WHITE);
  }
}

void stopGame(Game *game) {
  destroyMap(&game->map);
  destroyPlayer(&game->player);
}

