#include "map.h"
#include "resources.h"
#include <raylib.h>

Tile createTile(Texture2D *texture, TileType type, Vector2 position,
                TileAttribute *tile_attributes, size_t tile_attribute_size) {
  return (Tile){.texture = texture,
                .tile_type = type,
                .position = position,
                .collision_rect = (Rectangle){.x = position.x,
                                              .y = position.y,
                                              .width = texture->width,
                                              .height = texture->height},
                .tile_attributes = tile_attributes,
                .tile_attribute_size = tile_attribute_size};
}

Map createMap(int level_id, ResourceManager_t *rs_manager) {
  Tile *tiles_arr = (Tile *)malloc(sizeof(Tile) * MAX_TILES);
  if (tiles_arr == NULL) {
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }
  
  /* LOAD RESOURCES */
  loadResource(rs_manager, "crate", PATH_CRATE_IMAGE, true);
  loadResource(rs_manager, "bg_palm", PATH_BG_PALM_IMAGE, true);
  loadResource(rs_manager, "fg_palm_large", PATH_FG_PALM_LARGE_IMAGE, true);
  loadResource(rs_manager, "fg_palm_small", PATH_FG_PALM_SMALL_IMAGE, true);

  /* LOAD SPRITESHEETS */ 
  loadSpritesheet(rs_manager, "terrain", PATH_TERRAIN_SPRITESHEET);
  loadSpritesheet(rs_manager, "grass", PATH_GRASS_SPRITESHEET); 
  //loadSpritesheet(rs_manager, "coin", PATH_COIN_SPRITESHEET); 

  /* CHECK RESOURCES */
  Resource_t *crate_resource = getResource(rs_manager, "crate");
  if (crate_resource == NULL) {
    printf("Fejl i indhentning af crate resource\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }
  
  Resource_t *bg_palm_resource = getResource(rs_manager, "bg_palm");
  if (bg_palm_resource == NULL) {
    printf("Fejl i indhentning af bg_palm resource\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }
  
  Resource_t *fg_palm_large_resource = getResource(rs_manager, "fg_palm_large");
  if (fg_palm_large_resource == NULL) {
    printf("Fejl i indhentning af fg_palm_large resource\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }

  Resource_t *fg_palm_small_resource = getResource(rs_manager, "fg_palm_small");
  if (fg_palm_small_resource == NULL) {
    printf("Fejl i indhentning af fg_palm_small resource\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }

  /* CHECK SPRITESHEETS */
  // Terrain
  Spritesheet_t *terrain_sheet = getSpritesheet(rs_manager, "terrain");
  if (terrain_sheet == NULL) {
    printf("Fejl: kunne ikke indhente terrain spritesheet\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }
 
  Spritesheet_t *grass_sheet = getSpritesheet(rs_manager, "grass");
  if (grass_sheet == NULL) {
    printf("Fejl: kunne ikke indhente grass spritesheet\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }

  // Coins
  /*
  Spritesheet_t *coin_sheet = getSpritesheet(rs_manager, "coin");
  if (coin_sheet == NULL) {
    printf("Fejl: kunne ikke indhente coin spritesheet\n");
    free(tiles_arr);
    return (Map){.tiles_arr = NULL, .arr_size = 0};
  }
  */

  
  /* CREATE TILEGROUPS */
  TileGroup terrain_group = createTileGroup(
      PATH_TERRAIN_CSV, terrain_sheet->sliced_images,
      terrain_sheet->count, NULL, TYPE_TILE_TERRAIN);

  
  TileGroup crate_group = createTileGroup(PATH_CRATE_CSV, NULL, 0, &crate_resource->texture, TYPE_TILE_CRATE);
  TileGroup grass_group = createTileGroup(PATH_GRASS_CSV, grass_sheet->sliced_images, grass_sheet->count, NULL, TYPE_TILE_GRASS);
  TileGroup bg_palm_group = createTileGroup(PATH_BG_PALM_CSV, NULL, 0, &bg_palm_resource->texture, TYPE_TILE_BG_PALM);
  TileGroup fg_palm_large_group = createTileGroup(PATH_FG_PALM_CSV, NULL, 0, &fg_palm_large_resource->texture, TYPE_TILE_FG_PALM_LARGE);
  TileGroup fg_palm_small_group = createTileGroup(PATH_FG_PALM_CSV, NULL, 0, &fg_palm_small_resource->texture, TYPE_TILE_FG_PALM_SMALL);

  /* 
  TileGroup coin_group = createTileGroup(PATH_COIN_CSV, coin_sheet->sliced_images, coin_sheet->count, NULL, TYPE_TILE_COIN); 
*/
  size_t tiles_size = 0;
  insertTiles(&bg_palm_group, tiles_arr, &tiles_size);
  insertTiles(&crate_group, tiles_arr, &tiles_size);
  insertTiles(&terrain_group, tiles_arr, &tiles_size);
  insertTiles(&grass_group, tiles_arr, &tiles_size);
  insertTiles(&fg_palm_large_group, tiles_arr, &tiles_size);
  //insertTiles(&coin_group, tiles_arr, &tiles_size);

  return (Map){
      .tiles_arr = tiles_arr, .arr_size = tiles_size, .rs_manager = rs_manager};
}

void insertTiles(TileGroup *group, Tile *tile_arr, size_t *size_ptr) {
  for (size_t i = 0; i < group->tiles_size; ++i) {
    tile_arr[(*size_ptr)++] = group->tiles[i];
  }
}

TileGroup createTileGroup(const char *csv_path, Texture2D *sliced_images,
                          size_t sliced_images_len, Texture2D *single_texture,
                          TileType tile_type) {

  const float CRATE_Y_OFFSET = 23.0f;
  const float BG_PALM_Y_OFFSET = -64.0f;
  Tile *tile_arr = (Tile *)malloc(sizeof(Tile) * MAX_TILES);
  size_t tiles_size = 0;

  // Map struct
  Texture2D *texture_ptr = NULL;
  Vector2 position = (Vector2){0, 0};
  TileAttribute *attributes = NULL;
  size_t attribute_size = 0;

  int map[ROWS][COLS];
  if (readCSVToMap(csv_path, ROWS, COLS, map)) {
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {

        int value = map[i][j];
        if (value != -1) {
          if (sliced_images != NULL) {
            if (value >= sliced_images_len) {
              fprintf(stderr,
                      "Fejl: value %d uden for sliced_images længde %zu i %s\n",
                      value, sliced_images_len, csv_path);
              continue;
            }
          }

          if (single_texture != NULL) {
            texture_ptr = single_texture;
          } else {
            texture_ptr = &sliced_images[value];
          }

          position = (Vector2){j * TILE_SIZE, i * TILE_SIZE};
          switch (tile_type) {
          case TYPE_TILE_TERRAIN:
            static TileAttribute terrain_attrs[] = {ATTRIBUTE_COLLIDEABLE};
            attributes = terrain_attrs;
            attribute_size = 1;
            break;

          case TYPE_TILE_PLAYER_SETUP:
            static TileAttribute setup_attrs[] = {ATTRIBUTE_INVISIBLE};
            attributes = setup_attrs;
            attribute_size = 1;
            break;
          case TYPE_TILE_CRATE:
            static TileAttribute crate_attrs[] = {ATTRIBUTE_COLLIDEABLE};
            attributes = crate_attrs;
            attribute_size = 1;
            position.y += CRATE_Y_OFFSET;
            break;
          case TYPE_TILE_GRASS:
            static TileAttribute grass_attrs[] = {ATTRIBUTE_DECORATION};
            attributes = grass_attrs;
            attribute_size = 1;
            break;
          case TYPE_TILE_BG_PALM:
            static TileAttribute bg_palm_attrs[] = {ATTRIBUTE_DECORATION};
            attributes = bg_palm_attrs;
            attribute_size = 1;
            position.y -= 64;
            break;
            case TYPE_TILE_FG_PALM_LARGE: 
            case TYPE_TILE_FG_PALM_SMALL:
            static TileAttribute fg_palm_attrs[] = {ATTRIBUTE_COLLIDEABLE};
            attributes = fg_palm_attrs;
            attribute_size = 1;
            position.y += BG_PALM_Y_OFFSET;
            break;
          /*
            case TYPE_TILE_COIN:
            static TileAttribute coin_attrs[] = {ATTRIBUTE_COLLIDEABLE};
            attributes = coin_attrs;
            attribute_size = 1;
            break;
          */
            default:
            attributes = NULL;
            attribute_size = 0;
            break;
          }

          tile_arr[tiles_size++] = createTile(texture_ptr, tile_type, position,
                                              attributes, attribute_size);
        }
      }
    }
  }

  return (TileGroup){.tiles = tile_arr, .tiles_size = tiles_size};
}

void updateTile(Tile *tile) {}

void drawTile(Tile *tile) {
  for (size_t i = 0; i < tile->tile_attribute_size; ++i) {
    if (tile->tile_attributes[i] == ATTRIBUTE_INVISIBLE)
      return;
  }

  DrawTextureV(*(tile->texture), tile->position, WHITE);
}

// Update tiles
void updateMap(Map *map) {
  for (size_t i = 0; i < map->arr_size; ++i) {
    updateTile(&map->tiles_arr[i]);
  }
}

void destroyMap(Map *map) { free(map->tiles_arr); }
