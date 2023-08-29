// get user key input
#include <graphx.h>
#include <debug.h>
#include <stdlib.h>
#include <string.h>
#include <compression.h>
#include "gfx/growmi_bg.h"
#include "gfx/tileset.h"
#include "snake.h"
#include "tiles.h"
#include "gfx/gfx.h"

/* extern unsigned char tilemap_map[]; */

int main(void) {
    uint8_t key;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;

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
    tilemap.draw_height = 10;
    tilemap.draw_width = 13;
    tilemap.height = 10;
    tilemap.width = 13;
    tilemap.y_loc = 0;
    tilemap.x_loc = 0;
    Snake snake = SNAKE_init();

    gfx_Begin();
    /* gfx_SetTransparentColor(0); */
    /* gfx_SetDrawBuffer(); */

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    zx7_Decompress(gfx_vram, growmi_bg_compressed);
    do {
        gfx_Tilemap_NoClip(&tilemap, x_offset, y_offset);
        gfx_SetColor(0);
        gfx_FillRectangle(50,50,100,100);
        /* gfx_FillScreen(32); */
        // clear the screen
        /* SNAKE_move(&snake); */
        /* SNAKE_draw(&snake); */
        /* gfx_SwapDraw(); */
    } while (1 == 1);
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
