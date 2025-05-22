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

  Map map = createMap(
    0, // level id
    (Resources) {terrain_spritesheet, player_setup_spritesheet} // spritesheets
  );


  Player player = createPlayer(getPlayerSpawnPos());

  return (Game) {
    .player = player,
    .map = map,
  };
}

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
  bool collideable = false;

  for(size_t i = 0; i < game->map.arr_size; ++i) {

    // Check attributes
    for(size_t j = 0; j < game->map.tiles_arr[i].tile_attribute_size; ++j) {
      if(game->map.tiles_arr[i].tile_attributes[j] == ATTRIBUTE_COLLIDEABLE) collideable = true;
    }

    if(!collideable) return;

    if(CheckCollisionRecs(game->map.tiles_arr[i].collision_rect, game->player.collision_rect)) {
      if(game->player.direction.x < 0) {
        game->player.collision_rect.x = game->map.tiles_arr[i].collision_rect.x + game->map.tiles_arr[i].collision_rect.width;
      } else if(game->player.direction.x > 0) {
        game->player.collision_rect.x = game->map.tiles_arr[i].collision_rect.x - game->player.collision_rect.width;
      }
    }

    collideable = false; // Reset check
  }
}

void vertical_movement_collision(Game *game) {
  applyGravity(&game->player);
  game->player.on_ground = false;
  bool collideable = false;

  for(size_t i = 0; i < game->map.arr_size; ++i) {

    // Check attributes
    for(size_t j = 0; j < game->map.tiles_arr[i].tile_attribute_size; ++j) {
      if(game->map.tiles_arr[i].tile_attributes[j] == ATTRIBUTE_COLLIDEABLE) collideable = true;
    }

    if(!collideable) return;

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

    collideable = false;
  }

}

Vector2 getPlayerSpawnPos() {
  int map[ROWS][COLS];
  if(readCSVToMap("levels/0/level_0_player.csv", ROWS, COLS, map)) {
    for(int i = 0; i < ROWS; ++i) {
      for(int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if(value == 0) {
          return (Vector2) {j * TILE_SIZE, i * TILE_SIZE};
        }
      }
    }
  }

  return (Vector2) {0, 0};
}

void stopGame(Game *game) {
  destroyMap(&game->map);
  destroyPlayer(&game->player);
}

