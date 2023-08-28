// get user key input
#include <graphx.h>
#include <debug.h>
#include <stdlib.h>
#include <string.h>
#include "gfx/clouds.h"
#include "gfx/tileset.h"
#include "snake.h"
#include "tiles.h"
#include "gfx/gfx.h"

/* extern unsigned char tilemap_map[]; */
gfx_sprite_t *tileset_tiles[128];

/* This is where the decompressed tilemap data is stored */
uint8_t tilemap_map[10 * 13];
int main(void) {
    uint8_t key;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;
    gfx_tilemap_t tilemap;
    gfx_sprite_t *tmp_ptr;

    /* Initialize the tilemap structure */
    unsigned char* map = malloc(18 * 14);
    memset(map, TileType_Transparent, 18 * 14);
    tilemap.map = map;
    tilemap.tiles = tileset_tiles;
    tilemap.type_width = 18;
    tilemap.type_height = 18;
    tilemap.tile_height = 18;
    tilemap.tile_width = 18;
    tilemap.draw_height = 10;
    tilemap.draw_width = 13;
    tilemap.height = 10;
    tilemap.width = 13;
    tilemap.y_loc = 0;
    tilemap.x_loc = 0;
    for (unsigned int i = 0; i < sizeof(tileset_tiles) / sizeof(gfx_sprite_t*); ++i) {
        tmp_ptr = gfx_MallocSprite(TILE_WIDTH, TILE_HEIGHT);
        zx7_Decompress(tmp_ptr, tileset_tiles_compressed[i]);
        tileset_tiles[i] = tmp_ptr;
    }
    /* Decompress the compressed tilemap */
    zx7_Decompress(tileset_tiles, tileset_tiles_compressed);

    Snake snake = SNAKE_init();

    gfx_Begin();
    /* gfx_Sprite(clouds, 0, 0); */
    gfx_SetTransparentColor(1);
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetDrawBuffer();
    do {
        gfx_Tilemap_NoClip(&tilemap, x_offset, y_offset);
        // clear the screen
        /* SNAKE_move(&snake); */
        /* SNAKE_draw(&snake); */
        gfx_SwapDraw();
    } while (!SHOULD_EXIT);
#ifdef DEBUG
    dbg_printf("exiting, cleaning up ... ");
#endif
    gfx_End();
    SNAKE_FREE(snake);
#ifdef DEBUG
    dbg_printf("success");
#endif
    return 0;
}
