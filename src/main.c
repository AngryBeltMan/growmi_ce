// get user key input
#include <graphx.h>
#include <debug.h>
#include <stdlib.h>
#include <string.h>
#include <compression.h>
#include "gfx/tileset.h"
#include "snake.h"
#include "tiles.h"
#include "screen_info.h"
#include "gfx/gfx.h"
/* extern unsigned char tilemap_map[]; */
#define DRAWCLOUD(x,y) \
    gfx_FillCircle(x + 20, y + 5, 20); \
    gfx_FillCircle(x, y, 12); \
    gfx_FillCircle(x + 45, y + 2, 12);
void draw_background(unsigned int bg_color) {
    gfx_SetColor(bg_color);
    gfx_FillRectangle(0,0, GAME_WIDTH, GAME_HEIGHT);
    gfx_SetColor(0);
    DRAWCLOUD(0, 0);
    DRAWCLOUD(45, 50);
    DRAWCLOUD(65, 120);
    DRAWCLOUD(165, 30);
    DRAWCLOUD(125, 92);
}
void view_color_pallete(unsigned int y) {
    for (unsigned int x = 0; x < 5; ++x) {
        for (unsigned int i = x * 51; i < (x + 1) * 51; ++i) {
            gfx_SetColor(i);
            gfx_FillRectangle((i - (x * 51)) * 7, (x * 10) + y, 7, 10);
        }
    }

}
int main(void) {
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;
    unsigned int bg_color = 18;

    gfx_tilemap_t tilemap = tileset_new();
    Snake snake = SNAKE_init();

    gfx_Begin();
    gfx_SetDrawBuffer();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    tilemap.map[(TILEMAP_WIDTH * 5) + 4] = TileType_PurpleBlock;
    tilemap.map[(TILEMAP_WIDTH * 5) + 5] = TileType_PurpleBlock;
    tilemap.map[(TILEMAP_WIDTH * 5) + 6] = TileType_PurpleBlock;
    /* zx7_Decompress(gfx_vram, growmi_bg_compressed); */
    /* gfx_SwapDraw(); */
    /* zx7_Decompress(gfx_vram, growmi_bg_compressed); */
    do {
        gfx_FillScreen(1);
        SNAKE_update(&snake, &tilemap);
        draw_background(bg_color);
        gfx_TransparentTilemap_NoClip(&tilemap, x_offset, y_offset);
        view_color_pallete(180);
        gfx_SwapDraw();
    } while (!SHOULD_EXIT);
    dbg_printf("exiting, cleaning up ... ");
    gfx_End();
    dbg_printf("success");
    return 0;
}
