#ifndef SNAKE_H
#define SNAKE_H
#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <compression.h>
#include "key_input.h"
#include "screen_info.h"
#include "gfx/gfx.h"
#include "gfx/global_palette.h"
#include "gfx/growmi_mag_tail.h"
#include "gfx/growmi_snake_head.h"
#define ABSOLUTE_MAX 6

#define OPEN_SPRITE(sprite,sprite_width, sprite_height, comp_sprite) \
    gfx_sprite_t *sprite;  \
    sprite = gfx_MallocSprite(sprite_width,sprite_height ); \
    zx0_Decompress(sprite, comp_sprite);

#define SNAKE_FREE(snake) \
    free(snake.snake_tail); \
    free(snake.snake_head);

static unsigned int SHOULD_EXIT = 0;
typedef struct {
    unsigned int x;
    unsigned int y;
} SnakeSegment;
typedef struct {
    unsigned int length;
    unsigned int max_length;
    SnakeSegment segments[ABSOLUTE_MAX];
    unsigned int magnitized;
    gfx_sprite_t *snake_tail;
    gfx_sprite_t *snake_head;
} Snake;

static inline void SNAKE_move(Snake *P_snake) {
    KeyInput input = get_input();
    if (input != InputOther) {
        switch (input) {
            case InputUp: {
                break;
            }
            default: {
                break;
            }
        }
    }
}
static inline void SNAKE_draw(Snake *P_snake) {
    /* gfx_Sprite(P_snake->snake_tail, P_snake->segments[0].x, P_snake->segments[0].y); */
    gfx_Sprite(P_snake->snake_head, P_snake->segments[0].x, P_snake->segments[0].y);
    for (unsigned int segment = 1; segment < P_snake->length; ++P_snake->length ) {
        gfx_SetColor(100);
        SnakeSegment *pos= &P_snake->segments[segment];
        gfx_FillRectangle(pos->x, pos->y,TILE_WIDTH, TILE_HEIGHT );
    }
}
static inline Snake SNAKE_init() {
    Snake snake = (Snake) {
        .length = 1,
        .max_length = 5
    };
    snake.magnitized = 0;
    snake.segments[0] = (SnakeSegment) {
        .x = 3 * TILE_WIDTH,
        .y = 3 * TILE_HEIGHT
    };
    OPEN_SPRITE(snake_tail, growmi_mag_tail_width, growmi_mag_tail_height, growmi_mag_tail_compressed);
    OPEN_SPRITE(snake_head, growmi_snake_head_width, growmi_snake_head_height, growmi_snake_head_compressed);
    snake.snake_tail = snake_tail;
    snake.snake_head = snake_head;
    return snake;
}
#endif
