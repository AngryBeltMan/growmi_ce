#ifndef SNAKE_H
#define SNAKE_H
#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <debug.h>
#include <compression.h>
#include "key_input.h"
#include "tiles.h"
#include "screen_info.h"
#include "gfx/gfx.h"
#include "gfx/global_palette.h"
#include "stdbool.h"
#define ABSOLUTE_MAX 8
#define CURRENT_SEGMENT P_snake->segments[P_snake->length - 1]
#define NEXT_SEGMENT P_snake->segments[P_snake->length]
#define PREVIOUS_SEGMENT P_snake->segments[P_snake->length - 2]

/* #define OPEN_SPRITE(sprite,sprite_width, sprite_height, comp_sprite) \ */
/*     gfx_sprite_t *sprite;  \ */
/*     sprite = gfx_MallocSprite(sprite_width,sprite_height ); \ */
/*     zx0_Decompress(sprite, comp_sprite); */
#define SNAKE_SET(pos,tile) tile_map->map[pos.x + (pos.y * 13)] = tile;
#define APPLY_GRAVITY() if (P_snake->falling) { snake_move(P_snake, tile_map, 0, 1); return; }


static unsigned int SHOULD_EXIT = 0;
typedef struct {
    unsigned int x;
    unsigned int y;
} SnakeSegment;
typedef struct {
    unsigned int length;
    unsigned int max_length;
    bool falling;
    SnakeSegment previous_movement;
    SnakeSegment segments[ABSOLUTE_MAX];
    bool key_up;
    struct {
        // the ability to pull magnet blocks
        unsigned int magnitized;
        // the ability to shrink when hitting the alpha key
        unsigned int self_shrink;
    } abilities;
} Snake;
// removes all of the segments on the snake and sets the length to one
// also removes the snake body tiles on the tile map
// does not change other snake properties like magnitized
void snake_clear(Snake *P_snake, gfx_tilemap_t *tile_map) {
    dbg_printf("clearing\n");
    for (unsigned int seg = 0; seg < P_snake->length; ++seg) {
        SNAKE_SET(P_snake->segments[seg], TileType_Transparent);
    }
    P_snake->segments[0] = CURRENT_SEGMENT;
    P_snake->length = 1;
    SNAKE_SET(P_snake->segments[0], TileType_SnakeHead);
}
// increases and decreases the snakes length
void snake_grow_shrink(Snake *P_snake, gfx_tilemap_t *tile_map) {
    // checks for the snake going backwards
    // checks if the length is greater than one otherwise previous segment would read some other block of memory
    if (P_snake->length > 1) {
        if ((NEXT_SEGMENT.x == PREVIOUS_SEGMENT.x) && (NEXT_SEGMENT.y == PREVIOUS_SEGMENT.y)) {
            // set the new snake head to the previous block
            SNAKE_SET(PREVIOUS_SEGMENT, TileType_SnakeHead);
            // delete the snake head
            SNAKE_SET(CURRENT_SEGMENT, TileType_Transparent);
            --P_snake->length;
            return;
        }
    }
    // prevents the snake from growing longer than its max length
    // called before the previous block of code because if it wasn't
    // the snake would be unable to shink because it would return before
    // checking if the snake was going backwards
    if (P_snake->length == P_snake->max_length) return;
    SNAKE_SET(NEXT_SEGMENT, TileType_SnakeHead);
    SNAKE_SET(CURRENT_SEGMENT, TileType_SnakeBody);
    ++P_snake->length;

}
static inline void snake_move(Snake *P_snake, gfx_tilemap_t *tile_map, unsigned int x_move,unsigned int y_move) {
    NEXT_SEGMENT = (SnakeSegment) {
        /*since it is going up the x position will remain the same*/
        .x = CURRENT_SEGMENT.x + x_move,
        /* adding will make it go up one */
        .y = CURRENT_SEGMENT.y + y_move,
    };
    // checks for collisions
    if (is_tile_solid(NEXT_SEGMENT.x, NEXT_SEGMENT.y, tile_map)) return;
    // if it is touching a solid underneath it then remove all of the segments
    if (is_tile_solid(NEXT_SEGMENT.x, NEXT_SEGMENT.y + 1, tile_map)) {
        // makes the next segment the current segment
        /* if (!P_snake->falling) ++P_snake->length; */
        ++P_snake->length;
        snake_clear(P_snake, tile_map);
        P_snake->falling = 0;
    } else {
        snake_grow_shrink(P_snake, tile_map);
    }
}

static inline void SNAKE_update(Snake *P_snake, gfx_tilemap_t *tile_map) {
    APPLY_GRAVITY();
    KeyInput input = get_input();
    if (input != InputOther && P_snake->key_up) {
        P_snake->key_up = 0;
        // Gets the current location of the snake so we can figure out where the new segment position is at
        /* SnakeSegment *P_current_location = &P_snake->segments[P_snake->length - 1]; */
        switch (input) {
            case InputUp: {snake_move(P_snake, tile_map, 0, -1); break; }
            case InputDown: { snake_move(P_snake, tile_map, 0, 1); break; }
            case InputLeft: {snake_move(P_snake, tile_map, -1, 0); break; }
            case InputRight: {snake_move(P_snake, tile_map, 1, 0); break; }
            case InputAlpha: { if (P_snake->abilities.self_shrink) snake_clear(P_snake, tile_map); P_snake->falling = 1; break; }
            default: break;
        }
        // Increment the snake length for now
        // TODO
    } else if (input == InputOther) {
        P_snake->key_up = 1;
    }
}


static inline Snake SNAKE_init() {
    Snake snake = (Snake) {
        .length = 1,
        .max_length = 5,
        .key_up = 1
    };
    snake.abilities.magnitized = 0;
    snake.abilities.self_shrink = 0;
    snake.falling = 0;
    snake.segments[0] = (SnakeSegment) {
        .x = 3,
        .y = 3
    };
    return snake;
}
#endif
