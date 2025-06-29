#include "game.h"
#include "resources.h"
#include <raylib.h>

Game createGame(ResourceManager_t *rs_manager) {

  return (Game){
      .player = createPlayer(),
      .map = createMap(0, rs_manager),
      .camera = initCamera(),
      .sky = initSky(),
      .water = initWater(),
  };
}

void runGame(Game *game) {
  updateMap(&game->map);
  updatePlayer(&game->player);
  animateWater(&game->water);

  horizontalMovementCollision(game);
  verticalMovementCollision(game);

  drawSky(&game->sky);
  drawMap(game);
  drawPlayer(&game->player, game->camera.offset);
}

void horizontalMovementCollision(Game *game) {
  Player *player = &game->player;
  Tile *tiles_arr = game->map.tiles_arr;

  player->collision_rect.x += player->direction.x * game->player.speed;

  bool collideable = false;
  for (size_t i = 0; i < game->map.arr_size; ++i) {

    // Check attributes
    for (size_t j = 0; j < tiles_arr[i].tile_attribute_size; ++j) {
      if (tiles_arr[i].tile_attributes[j] == ATTRIBUTE_COLLIDEABLE)
        collideable = true;
    }

    if (!collideable)
      continue;

    if (CheckCollisionRecs(tiles_arr[i].collision_rect,
                           player->collision_rect)) {
      if (player->direction.x < 0) {
        player->collision_rect.x =
            tiles_arr[i].collision_rect.x + tiles_arr[i].collision_rect.width;
      } else if (player->direction.x > 0) {
        player->collision_rect.x =
            tiles_arr[i].collision_rect.x - player->collision_rect.width;
      }
    }

    collideable = false; // Reset check
  }
}

void verticalMovementCollision(Game *game) {
  Player *player = &game->player;
  Tile *tiles_arr = game->map.tiles_arr;

  // gravity og ground check
  applyGravity(player);
  player->on_ground = false;

  bool collideable = false;
  for (size_t i = 0; i < game->map.arr_size; ++i) {

    // Check attributes
    for (size_t j = 0; j < tiles_arr[i].tile_attribute_size; ++j) {
      if (tiles_arr[i].tile_attributes[j] == ATTRIBUTE_COLLIDEABLE)
        collideable = true;
    }

    if (!collideable)
      continue;

    if (CheckCollisionRecs(tiles_arr[i].collision_rect,
                           player->collision_rect)) {
      if (player->direction.y > 0) {
        player->collision_rect.y =
            tiles_arr[i].collision_rect.y - player->collision_rect.height;
        player->on_ground = true;
        player->direction.y = 0;
      } else if (player->direction.y < 0) {
        player->collision_rect.y =
            tiles_arr[i].collision_rect.y + tiles_arr[i].collision_rect.height;
        player->direction.y = 0;
        player->on_ceiling = true;
      }
    }

    collideable = false;
  }

  if (player->on_ground && player->direction.y < 0 || player->direction.y > 1) {
    player->on_ground = false;
  }

  if (player->on_ceiling && player->direction.y > 0) {
    player->on_ceiling = false;
  }
}

void drawMap(Game *game) {
  customDraw(&game->camera, game->map.tiles_arr, game->map.arr_size, &game->player, &game->water);
}

void stopGame(Game *game) {
  destroySky(&game->sky);
  destroyWater(&game->water);
  destroyPlayer(&game->player);
  destroyMap(&game->map);
}

Player *getPlayer(Game *game) { return &game->player; }
