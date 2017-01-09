#ifndef MEMORY_ORG_H_
#define MEMORY_ORG_H_

#include <stdio.h>
#include <nds.h>

#define TILE_SIZE   8 * 8

#define MIRROR      (1 << 10) 
typedef struct sMemoryBases{
    int bg_map_base;
    int bg_tile_base;
    int obj_map_base;
    int obj_tile_base;
}MemoryBases;

typedef struct sBuf{
    u16* tile_buffer;
    u16* map_buffer;
    u16* palette_buffer;
}buffer;


#define BG_TILE_SUB             BG_TILE_RAM_SUB(bases.bg_tile_base)
#define BG_MAP_SUB              BG_MAP_RAM_SUB(bases.bg_map_base)
#define OBJ_GAME_TILE_SUB       BG_TILE_RAM_SUB(bases.obj_tile_base)
#define OBJ_GAME_MAP_SUB        BG_MAP_RAM_SUB(bases.obj_map_base)

#define BG_TILE_MAIN            BG_TILE_RAM(bases.bg_tile_base)
#define BG_MAP_MAIN				BG_MAP_RAM(bases.bg_map_base)
#define OBJ_GAME_TILE_MAIN      BG_TILE_RAM(bases.obj_tile_base)
#define OBJ_GAME_MAP_MAIN       BG_MAP_RAM(bases.obj_map_base)

#endif
