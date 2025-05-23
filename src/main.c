#include "raylib.h"

// Personal imports
#include "game/game.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800
#define WIN_NAME "Platformer Game"

#define DEBUG_MODE 1

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
  SetTargetFPS(60);

  Game game = createGame();
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    runGame(&game);
    if(DEBUG_MODE == 1) {
      Player *player = getPlayer(&game);
      DrawText(TextFormat("Player Position: (%02.2f, %02.2f)", player->position.x, player->position.y), 100, 30, 25, RED);
      DrawText(TextFormat("Player State: (%d)", player->state), 100, 60, 25, RED);
    }

    EndDrawing();
  }

  stopGame(&game);

  CloseWindow();
  return 0;
}
