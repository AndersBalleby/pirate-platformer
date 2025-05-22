#include "game.h"

Game createGame() {
  return (Game) {
    .player = createPlayer(),
    .map = createMap(0)
  };
}

// test
void runGame(Game *game) {
  updateMap(&game->map);
  updatePlayer(&game->player);

  horizontal_movement_collision(game);
  vertical_movement_collision(game);

  drawMap(&game->map);
  drawPlayer(&game->player);
}

void horizontal_movement_collision(Game *game) {
  game->player.collision_rect.x += game->player.direction.x * game->player.speed;

  for(size_t i = 0; i < game->map.arr_size; ++i) {
    if(CheckCollisionRecs(game->map.tiles_arr[i].collision_rect, game->player.collision_rect)) {
      if(game->player.direction.x < 0) {
        game->player.collision_rect.x = game->map.tiles_arr[i].collision_rect.x + game->map.tiles_arr[i].collision_rect.width;
      } else if(game->player.direction.x > 0) {
        game->player.collision_rect.x = game->map.tiles_arr[i].collision_rect.x - game->player.collision_rect.width;
      }
    }
  }
}

void vertical_movement_collision(Game *game) {
  applyGravity(&game->player);
  game->player.on_ground = false;

  for(size_t i = 0; i < game->map.arr_size; ++i) {
    if(CheckCollisionRecs(game->map.tiles_arr[i].collision_rect, game->player.collision_rect)) {
      if(game->player.direction.y > 0) {
        game->player.collision_rect.y = game->map.tiles_arr[i].collision_rect.y - game->player.collision_rect.height;
        game->player.on_ground = true;
        game->player.direction.y = 0;
      } else if(game->player.direction.y < 0) {
        game->player.collision_rect.y = game->map.tiles_arr[i].collision_rect.y + game->map.tiles_arr[i].collision_rect.height;
        game->player.direction.y = 0;
      }
    }
  }

}

void stopGame(Game *game) {
  destroyMap(&game->map);
  destroyPlayer(&game->player);
}

