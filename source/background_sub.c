#include "background_sub.h"

// Background of the game


void init_background_sub(struct sMemoryBases base)
{
    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    REG_DISPCNT = MODE_FB0;
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_LCD;


    BGCTRL_SUB[2] = BG_COLOR_256 | BG_32x32
                    | BG_MAP_BASE(base.bg_map_base)
                    | BG_TILE_BASE(base.bg_tile_base);

    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256
                    | BG_MAP_BASE(base.obj_map_base)
                    | BG_TILE_BASE(base.obj_tile_base);
}

void store_image_background_sub(struct sBuf bf){
    memcpy(bf.tile_buffer, cosmos2Tiles, cosmos2TilesLen);
    memcpy(bf.palette_buffer, cosmos2Pal, cosmos2PalLen);
    memcpy(bf.map_buffer, cosmos2Map, cosmos2MapLen);
}
