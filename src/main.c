#include "../include/resource_dir.h"
#include "raylib.h"

// Personal imports
#include "game/game.h"
#include "game/map.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800
#define WIN_NAME "Platformer Game"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
  SetTargetFPS(60);

  Game game = createGame();
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    runGame(&game);

    EndDrawing();
  }

  stopGame(&game);

  CloseWindow();
  return 0;
}
