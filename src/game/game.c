#include "game.h"

Game createGame() {

  Spritesheet terrain_spritesheet = loadSpritesheet(TERRAIN_SPRITESHEET);
  if (terrain_spritesheet.sliced_images == NULL || terrain_spritesheet.count == 0) {
    perror("kunne ikke indlæse spritesheet fra terrain tiles");
    exit(-1); //todo find på noget bedre her
  }

  Spritesheet player_setup_spritesheet = loadSpritesheet(PLAYER_SETUP_SPRITESHEET);
  if (player_setup_spritesheet.sliced_images == NULL || player_setup_spritesheet.count == 0) {
    perror("kunne ikke indlæse spritesheet fra player setup");
    exit(-1); //todo find på noget bedre her
  }

  return (Game) {
    .player = createPlayer(),
    .map = createMap(
      0, // level id
      (Resources) {terrain_spritesheet, player_setup_spritesheet} // spritesheets
    ),
    .camera = initCamera()
  };
}

void runGame(Game *game) {
  updateMap(&game->map);
  updatePlayer(&game->player);

  horizontalMovementCollision(game);
  verticalMovementCollision(game);

  drawMap(&game->camera, &game->player, &game->map);
  drawPlayer(&game->player, game->camera.offset);
}

void horizontalMovementCollision(Game *game) {
  Player *player = &game->player;
  Tile *tiles_arr = game->map.tiles_arr;

  player->collision_rect.x += player->direction.x * game->player.speed;
  
  bool collideable = false;
  for(size_t i = 0; i < game->map.arr_size; ++i) {

    // Check attributes
    for(size_t j = 0; j < tiles_arr[i].tile_attribute_size; ++j) {
      if(tiles_arr[i].tile_attributes[j] == ATTRIBUTE_COLLIDEABLE) collideable = true;
    }

    if(!collideable) return;

    if(CheckCollisionRecs(tiles_arr[i].collision_rect, player->collision_rect)) {
      if(player->direction.x < 0) {
        player->collision_rect.x = tiles_arr[i].collision_rect.x + tiles_arr[i].collision_rect.width;
      } else if(player->direction.x > 0) {
        player->collision_rect.x = tiles_arr[i].collision_rect.x - player->collision_rect.width;
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
  for(size_t i = 0; i < game->map.arr_size; ++i) {

    // Check attributes
    for(size_t j = 0; j < tiles_arr[i].tile_attribute_size; ++j) {
      if(tiles_arr[i].tile_attributes[j] == ATTRIBUTE_COLLIDEABLE) collideable = true;
    }

    if(!collideable) return;

    if(CheckCollisionRecs(tiles_arr[i].collision_rect, player->collision_rect)) {
      if(player->direction.y > 0) {
        player->collision_rect.y = tiles_arr[i].collision_rect.y - player->collision_rect.height;
        player->on_ground = true;
        player->direction.y = 0;
      } else if(player->direction.y < 0) {
        player->collision_rect.y = tiles_arr[i].collision_rect.y + tiles_arr[i].collision_rect.height;
        player->direction.y = 0;
        player->on_ceiling = true;
      }
    }

    collideable = false;
  }

  if (player->on_ground && player->direction.y < 0 || player->direction.y > 1) {
    player->on_ground = false;
  }

  if(player->on_ceiling && player->direction.y > 0) {
    player->on_ceiling = false;
  }

}

void drawMap(P_Camera *camera, Player *player, Map *map) {
  customDraw(camera, map->tiles_arr, map->arr_size, player);
}

void stopGame(Game *game) {
  destroyMap(&game->map);
  destroyPlayer(&game->player);
}

Player *getPlayer(Game *game) {
  return &game->player;
}
