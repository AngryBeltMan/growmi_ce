// get user key input
#include <graphx.h>
#include <debug.h>
#include <stdlib.h>
#include <string.h>
#include <compression.h>
#include "gfx/clouds.h"
#include "gfx/tileset.h"
#include "snake.h"
#include "tiles.h"
#include "gfx/gfx.h"

/* extern unsigned char tilemap_map[]; */

int main(void) {
    uint8_t key;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;
    gfx_sprite_t *background;
    background = gfx_MallocSprite(clouds_width,clouds_height);
    zx7_Decompress(background, clouds_compressed);
    gfx_tilemap_t tilemap;

    /* Initialize the tilemap structure */
    unsigned char* map = malloc(18 * 14);
    memset(map, TileType_Transparent, 18 * 14);
    tilemap.map = map;
    tilemap.tiles = tileset_tiles;
    tilemap.type_width = 18;
    tilemap.type_height = 18;
    tilemap.tile_height = 18;
    tilemap.tile_width = 18;
    tilemap.draw_height = 18;
    tilemap.draw_width = 14;
    tilemap.height = 10;
    tilemap.width = 13;
    tilemap.y_loc = 0;
    tilemap.x_loc = 0;
    Snake snake = SNAKE_init();

    gfx_Begin();
    /* gfx_SetTransparentColor(1); */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetDrawBuffer();
    do {
        gfx_Sprite(background, 0, 0);
        gfx_Tilemap_NoClip(&tilemap, x_offset, y_offset);
        gfx_FillScreen(1);
        // clear the screen
        /* SNAKE_move(&snake); */
        /* SNAKE_draw(&snake); */
        gfx_SwapDraw();
    } while (1 == 1);
#ifdef DEBUG
    dbg_printf("exiting, cleaning up ... ");
#endif
    free(background);
    gfx_End();
    SNAKE_FREE(snake);
#ifdef DEBUG
    dbg_printf("success");
#endif
    return 0;
}
