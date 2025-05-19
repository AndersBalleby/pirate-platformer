#include "../include/resource_dir.h"
#include "raylib.h"

// Personal imports
#include "game/game.h"
#include "game/player.h"
#include "game/map.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800
#define WIN_NAME "Platformer Game"

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);

  SearchAndSetResourceDir("resources");
  
  SetTargetFPS(60); // Vi kører på 60 fps :)
  Player *player = createPlayer();
 
  generateMap(0);
  
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    
    run_game();
    update(player);
    drawPlayer(player);

    EndDrawing();
  }

  destroyPlayer(player);

  CloseWindow();
  return 0;
}
