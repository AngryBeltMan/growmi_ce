#ifndef COLLISION_H
#define COLLISION_H
#include "snake.h"
#include "tiles.h"
#include "screen_info.h"
typedef enum {
   CollisionType_SNAKE,
   CollisionType_BOX,
   CollisionType_WALL,
   CollisionType_None,
} CollisionType;

static inline CollisionType COLLISION_check(Snake *P_snake, SnakeSegment future_pos) {
    for (unsigned int segments = 0; segments < P_snake->length; ++segments) {}
}
static inline TileType get_colliding_type() {

}
#endif
