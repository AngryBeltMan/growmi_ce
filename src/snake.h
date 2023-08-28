#ifndef SNAKE_H
#define SNAKE_H
#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <debug.h>
#include <compression.h>
#include "key_input.h"
#include "screen_info.h"
#include "gfx/gfx.h"
#include "gfx/global_palette.h"
#define ABSOLUTE_MAX 6

/* #define OPEN_SPRITE(sprite,sprite_width, sprite_height, comp_sprite) \ */
/*     gfx_sprite_t *sprite;  \ */
/*     sprite = gfx_MallocSprite(sprite_width,sprite_height ); \ */
/*     zx0_Decompress(sprite, comp_sprite); */

#define SNAKE_FREE(snake)
    /* free(snake.snake_tail); \ */
    /* free(snake.snake_head); */
#define SNAKE_MOVEMENT_MATCH(match_arm, x_move, y_move) \
    case match_arm: { \
        P_snake->segments[P_snake->length] = (SnakeSegment) { \
            /*since it is going up the x position will remain the same*/ \
            .x = P_current_location->x + x_move, \
            /* adding will make it go up one */ \
            .y = P_current_location->y + y_move, \
        }; \
        break; \
    }

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
    /* gfx_sprite_t *snake_tail; */
    /* gfx_sprite_t *snake_head; */
    unsigned int key_up;
} Snake;
/* static inline  */
static inline void SNAKE_move(Snake *P_snake) {
    KeyInput input = get_input();
    dbg_printf("arm %i\n", input);
    if (input != InputOther && P_snake->key_up) {
        P_snake->key_up = 0;
        // Gets the current location of the snake so we can figure out where the new segment position is at
        SnakeSegment *P_current_location = &P_snake->segments[P_snake->length - 1];
        switch (input) {
            SNAKE_MOVEMENT_MATCH(InputUp, 0, -TILE_HEIGHT)
            SNAKE_MOVEMENT_MATCH(InputDown, 0, TILE_HEIGHT)
            SNAKE_MOVEMENT_MATCH(InputLeft, -TILE_WIDTH, 0)
            SNAKE_MOVEMENT_MATCH(InputRight, TILE_WIDTH, 0)
            default: break;
        }
        // Increment the snake length for now
        // TODO
        ++P_snake->length;
    } else if (input == InputOther) {
        P_snake->key_up = 1;
    }
}

static inline void SNAKE_draw(Snake *P_snake) {
    /* gfx_Sprite(P_snake->snake_head, P_snake->segments[0].x, P_snake->segments[0].y); */
    for (unsigned int segment = 1; segment < P_snake->length; ++segment ) {
        gfx_SetColor(100);
        SnakeSegment *pos= &P_snake->segments[segment];
        gfx_FillRectangle(pos->x, pos->y,TILE_WIDTH, TILE_HEIGHT );
    }
}

static inline Snake SNAKE_init() {
    Snake snake = (Snake) {
        .length = 1,
        .max_length = 5,
        .key_up = 1
    };
    snake.magnitized = 0;
    snake.segments[0] = (SnakeSegment) {
        .x = 3 * TILE_WIDTH,
        .y = 3 * TILE_HEIGHT
    };
    /* OPEN_SPRITE(snake_tail, growmi_mag_tail_width, growmi_mag_tail_height, growmi_mag_tail_compressed); */
    /* OPEN_SPRITE(snake_head, growmi_snake_head_width, growmi_snake_head_height, growmi_snake_head_compressed); */
    /* snake.snake_tail = snake_tail; */
    /* snake.snake_head = snake_head; */
    return snake;
}
#endif
