#include "player.h"
#include <raylib.h>

Player createPlayer() { // Refactor senere
  
  PlayerAnimations *animations = loadPlayerAnimations();
  Texture2D idle_texture = animations->idle_animations[0];
  Vector2 spawn_pos = getSpawnPos();
  Rectangle collision_rect =
      (Rectangle){spawn_pos.x, spawn_pos.y, idle_texture.width, idle_texture.height};

  return (Player){
      .texture = idle_texture,
      .position = spawn_pos,
      .direction = (Vector2){0, 0},
      .collision_rect = collision_rect,
      .speed = PLAYER_SPEED,
      .on_ground = false,
      .on_ceiling = false,
      .on_right = true,
      .last_jump_time = 0.0,
      .gravity = GRAVITY,
      .state = PLAYER_STATE_IDLE,
      .animations = animations
  };
}

PlayerAnimations *loadPlayerAnimations() {
  PlayerAnimations *animations = (PlayerAnimations *) malloc(sizeof(PlayerAnimations));

  animations->idle_animations[0] = LoadTexture("resources/character/idle/1.png");
  animations->idle_animations[1] = LoadTexture("resources/character/idle/2.png");
  animations->idle_animations[2] = LoadTexture("resources/character/idle/3.png");
  animations->idle_animations[3] = LoadTexture("resources/character/idle/4.png");
  animations->idle_animations[4] = LoadTexture("resources/character/idle/5.png");

  animations->fall_animations[0] = LoadTexture("resources/character/fall/fall.png");

  animations->jump_animations[0] = LoadTexture("resources/character/jump/1.png");
  animations->jump_animations[1] = LoadTexture("resources/character/jump/2.png");
  animations->jump_animations[2] = LoadTexture("resources/character/jump/3.png");

  animations->run_animations[0] = LoadTexture("resources/character/run/1.png");
  animations->run_animations[1] = LoadTexture("resources/character/run/2.png");
  animations->run_animations[2] = LoadTexture("resources/character/run/3.png");
  animations->run_animations[3] = LoadTexture("resources/character/run/4.png");
  animations->run_animations[4] = LoadTexture("resources/character/run/5.png");
  animations->run_animations[5] = LoadTexture("resources/character/run/6.png");

  return animations;
}

void updatePlayer(Player *player) {
  getInput(player);
  updatePlayerState(player);
  animate(player);

  player->position.x = player->collision_rect.x;
  player->position.y = player->collision_rect.y;
}

void getInput(Player *player) {
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    player->direction.x = -1;
    player->on_right = false;
  } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    player->direction.x = 1;
    player->on_right = true;
  } else {
    player->direction.x = 0;
  }

  if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) &&
      player->on_ground) {
    jump(player);
  }
}

void updatePlayerState(Player *player) {
  if (!(player->on_ground) && player->direction.y > 0) {
    player->state = PLAYER_STATE_FALLING;
    return;
  } else if (!(player->on_ground) && player->direction.y < 0) {
    player->state = PLAYER_STATE_JUMPING;
    return;
  }

  if (player->direction.x == 0) {
    player->state = PLAYER_STATE_IDLE;
  } else if (player->direction.x > 0 || player->direction.x < 0) {
    player->state = PLAYER_STATE_RUNNING;
  }
}

void checkFrames(Player *player, int max_frames) { 
  if(player->animation_frame >= max_frames) {
    player->animation_frame = 0;
  }

}

void animate(Player *player) { 
  Texture2D current_frame;
  switch(player->state) {

    case PLAYER_STATE_IDLE:
      checkFrames(player, 5);
      current_frame = player->animations->idle_animations[(int) player->animation_frame];
      break;
    
    case PLAYER_STATE_FALLING:
      checkFrames(player, 0);
      current_frame = player->animations->fall_animations[(int) player->animation_frame]; // kun 1 animation
    
    case PLAYER_STATE_RUNNING:
      checkFrames(player, 6);
      current_frame = player->animations->run_animations[(int) player->animation_frame];
      break;
    
    case PLAYER_STATE_JUMPING:
      checkFrames(player, 3);
      current_frame = player->animations->jump_animations[(int) player->animation_frame];
      break;
    default:
      break;
  }

  player->texture = current_frame;
  player->animation_frame += ANIMATION_SPEED;
}

void jump(Player *player) { player->direction.y = JUMP_SPEED; }

void applyGravity(Player *player) {
  player->direction.y += player->gravity;
  player->collision_rect.y += player->direction.y;
}

void drawPlayer(Player *player, Vector2 offset) {
  int tallest_frame_height = 58;
 
  int y_offset = tallest_frame_height - player->texture.height;
  Vector2 screenPos = {player->position.x - offset.x,
                       player->position.y - offset.y + y_offset};

  Rectangle source = {0.0f, 0.0f, (float)-player->texture.width,
                      (float)player->texture.height};
 

  //Vector2 draw_position = { player->position.x, player->position.y + y_offset };

  if (player->on_right) {
    DrawTexture(player->texture, screenPos.x, screenPos.y, WHITE);
  } else {
    DrawTextureRec(player->texture, source, screenPos, WHITE);
  }

  /// WHITE);

  /* Collision Box

  DrawTextureV(player->texture, player->position, WHITE);
  DrawRectangleLines(
    (int)player->collision_rect.x,
    (int)player->collision_rect.y,
    (int)player->collision_rect.width,
    (int)player->collision_rect.height,
    RED
    );

*/
}

Vector2 getSpawnPos() {
  int map[ROWS][COLS];
  if (readCSVToMap("levels/0/level_0_player.csv", ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        int value = map[i][j];
        if (value == 0) {
          return (Vector2){j * TILE_SIZE, i * TILE_SIZE};
        }
      }
    }
  }

  return (Vector2){0, 0};
}

void destroyPlayer(Player *player) { 
  for(int i = 0; i < 5; ++i) {
   UnloadTexture(player->animations->idle_animations[i]); 
  }

  UnloadTexture(player->animations->fall_animations[0]);
  
  for(int i = 0; i < 3; ++i) {
    UnloadTexture(player->animations->jump_animations[i]);  
  }

  for(int i = 0; i < 6; ++i) {
    UnloadTexture(player->animations->run_animations[i]);
  }

  free(player->animations);
}
