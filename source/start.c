
#include "start.h"
#include "01_hello.h"
// Background MAIN screen

void draw_bg_main_screen(){

    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_5_2D  | DISPLAY_BG2_ACTIVE;
    BGCTRL[2] =  BG_BMP_BASE(0) | BgSize_B8_256x256 ;   // Main
    // Affine Marix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;

    swiCopy(start_topBitmap, BG_BMP_RAM(0), start_topBitmapLen/2);
    swiCopy(start_topPal, BG_PALETTE, start_topPalLen/2);
}

void draw_sequence_story_sub_screen(){

    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
    REG_DISPCNT_SUB = MODE_5_2D  | DISPLAY_BG2_ACTIVE;
    BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256; //Sub

    // Affine Marix Transformation

    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    swiCopy(_1_helloBitmap, BG_BMP_RAM_SUB(0), _1_helloBitmapLen/2);
    swiCopy(_1_helloPal, BG_PALETTE_SUB, _1_helloPalLen/2);
}


void display_start()
{
    // Switch backgrounds to palettes
    draw_bg_main_screen();
    draw_sequence_story_sub_screen();

    // Print instructions on top screen


    // Print start menu on SUB screen
    /*if(AI){ // AI mode
        swiCopy(start_picBitmap, BG_BMP_RAM_SUB(0), start_picBitmapLen/2);
        swiCopy(start_picPal, BG_PALETTE_SUB, start_picPalLen/2);
    }
    else{ // PvP mode
        swiCopy(start_pic_1v1Bitmap, BG_BMP_RAM_SUB(0), start_pic_1v1BitmapLen/2);
        swiCopy(start_pic_1v1Pal, BG_PALETTE_SUB, start_pic_1v1PalLen/2);
    */

    //while(1);

}