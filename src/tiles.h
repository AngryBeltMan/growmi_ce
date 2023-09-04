#ifndef TILES_H
#define TILES_H
#include <graphx.h>
#define TILEMAP_WIDTH 13
#define TILEMAP_HEIGHT 10
#define TILE_WIDTH 18
#define TILE_HEIGHT 18
typedef enum {
    TileType_SnakeHead = 0x00,
    TileType_SnakeBody = 0x01,
    TileType_PurpleBlock = 0x02,
    TileType_Transparent = 0x03,
    TileType_MagnetTail = 0x04,
    TileType_Spikes = 0x05,
} TileType;
gfx_tilemap_t tileset_new() {
    gfx_tilemap_t tilemap;
    /* Initialize the tilemap structure */
    unsigned char* map = malloc(18 * 14);
    memset(map, TileType_Transparent, 18 * 14);
    tilemap.map = map;
    tilemap.tiles = tileset_tiles;
    tilemap.type_width = TILE_WIDTH;
    tilemap.type_height = TILE_HEIGHT;
    tilemap.tile_height = TILE_HEIGHT;
    tilemap.tile_width = TILE_WIDTH;
    tilemap.draw_height = TILEMAP_HEIGHT;
    tilemap.draw_width = TILEMAP_WIDTH;
    tilemap.height = TILEMAP_HEIGHT;
    tilemap.width = TILEMAP_WIDTH;
    tilemap.y_loc = 0;
    tilemap.x_loc = 0;
    return tilemap;
}
TileType get_tile_type(unsigned int x, unsigned int y, gfx_tilemap_t *tilemap) {
    return tilemap->map[(y * TILEMAP_WIDTH) + x];
}
unsigned int is_tile_solid(unsigned int x, unsigned int y, gfx_tilemap_t *tilemap) {
    TileType tile = get_tile_type(x, y, tilemap);
    switch (tile) {
        case TileType_PurpleBlock: return 1;
        default: return 0;
    }
}

#endif
