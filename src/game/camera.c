#include "camera.h"

P_Camera initCamera() {
  return (P_Camera){
    .offset = (Vector2){0, 0},
    .rect = (Rectangle){300, 350, 350, 200}, // box i midten af 800x600
  };
}


void boxTargetCamera(P_Camera *camera, Player *player) {
  // Find spillerens position i forhold til kamera-offset
  float playerScreenX = player->position.x - camera->offset.x;
  float playerScreenY = player->position.y - camera->offset.y;

  // Hvis spilleren bevæger sig uden for rect-boksen, justér kameraets offset
  if (playerScreenX < camera->rect.x) {
      camera->offset.x = player->position.x - camera->rect.x;
  } else if (playerScreenX > camera->rect.x + camera->rect.width) {
      camera->offset.x = player->position.x - (camera->rect.x + camera->rect.width);
  }

  if (playerScreenY < camera->rect.y) {
      camera->offset.y = player->position.y - camera->rect.y;
  } else if (playerScreenY > camera->rect.y + camera->rect.height) {
      camera->offset.y = player->position.y - (camera->rect.y + camera->rect.height);
  }
}

void drawTileWithOffset(Tile *tile, Vector2 offset) {
  Vector2 screenPos = {
      tile->position.x - offset.x,
      tile->position.y - offset.y
  };

  // Check tile attributes
  for(size_t i = 0; i < tile->tile_attribute_size; ++i) {
    if(tile->tile_attributes[i] == ATTRIBUTE_INVISIBLE) return;
  }
  
  DrawTexture(*tile->texture, (int)screenPos.x, (int)screenPos.y, WHITE);

  // Evt. tegne collision rect for debugging:
  //DrawRectangleLines(tile->collision_rect.x - offset.x, tile->collision_rect.y - offset.y, tile->collision_rect.width, tile->collision_rect.height, RED);
}

void customDraw(P_Camera *camera, Tile *tiles_arr, size_t tiles_size, Player *player) {
  boxTargetCamera(camera, player);

  for (size_t i = 0; i < tiles_size; ++i) {
      drawTileWithOffset(&tiles_arr[i], camera->offset);
  }

  // Debug: Tegn kameraets boks
  /*
  Rectangle debugRect = {
      camera->rect.x,
      camera->rect.y,
      camera->rect.width,
      camera->rect.height
  };
  DrawRectangleLinesEx(debugRect, 2.0f, RED);
  */
}



