#include "background_sub.h"
#include <stdio.h>
#include <stdlib.h>
#include "../data/cosmos2.h"

// Background of the game
void init_background_sub(){
    REG_DISPCNT_SUB = DISPLAY_BG2_ACTIVE | MODE_0_2D | DISPLAY_BG0_ACTIVE;
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
    BGCTRL_SUB[2] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2) | BG_32x32;
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(5);

}

void store_image_background_sub(){
    swiCopy(cosmos2Tiles, BG_TILE_RAM_SUB(2), cosmos2TilesLen/2);
    swiCopy(cosmos2Pal, BG_PALETTE_SUB, cosmos2PalLen/2);
    swiCopy(cosmos2Map, BG_MAP_RAM_SUB(0), cosmos2MapLen/2);

    // int tiles = 0;
    // int i,j;
    // for (i = 1; i < 24; i++)
    //     for (j = 0; j < 4 ; j++){
    //         BG_MAP_RAM_SUB(0)[43 * i + j] = cosmos2Map[tiles];
    //         tiles++;
    //     }
}
