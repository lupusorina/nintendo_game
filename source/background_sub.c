#include "background_sub.h"

// Background of the game
void init_background_sub(){
    REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
    BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;
}

void store_image_background_sub(){
    swiCopy(cosmosPal, BG_PALETTE_SUB, cosmosPalLen);
    swiCopy(cosmosBitmap, BG_GFX_SUB, cosmosBitmapLen);

    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

}