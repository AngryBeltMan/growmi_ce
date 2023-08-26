// get user key input
#include <graphx.h>
#ifdef DEBUG
#include <debug.h>
#endif
#include <stdlib.h>
#include "snake.h"

int main(void) {
    Snake snake = SNAKE_init();
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    do {
        // clear the screen
        gfx_FillScreen(0);
        SNAKE_draw(&snake);
        gfx_Wait();
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
