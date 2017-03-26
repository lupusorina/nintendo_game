
#include "start.h"

#include "aliens.h"
#include "ai_vs_human.h"

// Background MAIN screen
void init_main_screen(){
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_5_2D  | DISPLAY_BG2_ACTIVE | DISPLAY_BG1_ACTIVE;
    BGCTRL[2] =  BG_BMP_BASE(0) | BgSize_B8_256x256 ;   // Main
}

void draw_bg_main_screen(){

    // Affine Marix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;

    swiCopy(start_topBitmap, BG_BMP_RAM(0), start_topBitmapLen/2);
    swiCopy(start_topPal, BG_PALETTE, start_topPalLen/2);
}

void delay(int time){
    int i;
    int a;
    for (i = 0; i < time; i++){
        a = 1;
    }
}

void init_sub_screen(){
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
    REG_DISPCNT_SUB = MODE_0_2D  | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
    BGCTRL_SUB[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;
    BGCTRL_SUB[1] = BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(1) | BG_32x32;
    BGCTRL_SUB[2] = BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(1) | BG_32x32;
    BGCTRL_SUB[3] = BG_COLOR_256 | BG_MAP_BASE(3) | BG_TILE_BASE(1) | BG_32x32;

    // Affine Marix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    swiCopy(aliensTiles, BG_TILE_RAM_SUB(1), aliensTilesLen/2);
    swiCopy(aliensPal, BG_PALETTE_SUB, aliensPalLen/2);

    swiCopy(&aliensMap[0], BG_MAP_RAM_SUB(1), 32*10);
    swiCopy(&aliensMap[32*11], BG_MAP_RAM_SUB(0), 32*11);
    swiCopy(&aliensMap[32*24], BG_MAP_RAM_SUB(2), 32*12);
}
void draw_start_screen(){

    init_sub_screen();

    int bg0_h = -90;
    int bg0_v = -40;

    int bg1_h = 90;
    int bg1_v = 0;
    int bg1_before = 90;
    int bg1_after = -90;

    int bg2_h = 90;
    int bg2_v = -80;

    int bg3_h = -35;
    int bg3_v = -35;

    REG_BG0HOFS_SUB = bg0_h;
    REG_BG0VOFS_SUB = bg0_v;

    REG_BG1HOFS_SUB = bg1_h;
    REG_BG1VOFS_SUB = bg1_v;

    REG_BG2HOFS_SUB = bg2_h;
    REG_BG2VOFS_SUB = bg2_v;

    REG_BG3HOFS_SUB = bg3_h;
    REG_BG3VOFS_SUB = bg3_v;

    int i;
    while (bg1_before !=  bg1_after){

        REG_BG1HOFS_SUB = bg1_before;
        REG_BG0HOFS_SUB = -bg1_before;
        REG_BG2HOFS_SUB = bg1_before;
        delay(5000);
        bg1_before --;
        //delay(5000);

    }
    audio_laser();
    swiCopy(&aliensMap[32*38], BG_MAP_RAM_SUB(3), 32*10);

}

void draw_part1(){

    int bg_before = 90;
    int bg0_after = 0;
    int bg_v = 0;
    while (bg0_after != bg_before){
        bg_before--;
        REG_BG0HOFS_SUB = bg_before;
        REG_BG0VOFS_SUB = bg_v;
        delay(10000);
    }

    int bg2_before_h = -90;
    int bg2_before_v = -80;
    int bg2_after_h = 90;
    int bg2_after_v = -10;

    int bg3_h = 0;
    int bg3_v = -90;

    while (bg2_before_h != bg2_after_h){
        bg2_before_h = bg2_before_h + 2;
        REG_BG2HOFS_SUB = bg2_before_h;
        if (bg2_before_v == bg2_after_v)
            REG_BG2VOFS_SUB = bg2_after_v;
        else
            bg2_before_v = bg2_before_v + 1;

        REG_BG3HOFS_SUB = bg3_h;
        REG_BG3VOFS_SUB = bg3_v;
        delay(10000);

    }

    REG_BG3HOFS_SUB = bg3_h;
    REG_BG3VOFS_SUB = bg3_v;
    delay(10000);


}

void ISR_TIMER0(){
    int static count = 0;
    count ++;
    if (count == 3){

    }
    if (count == 62){
        selection_mode_screen();
    }


}

void selection_mode_screen(){
    audio_stop_music();
    int offset_v = 0, offset_h = 0;
    REG_BG0HOFS_SUB = offset_v;
    REG_BG0VOFS_SUB = offset_h;
    swiCopy(ai_vs_humanTiles, BG_TILE_RAM_SUB(1), ai_vs_humanTilesLen/2);
    swiCopy(ai_vs_humanPal, BG_PALETTE_SUB, ai_vs_humanPalLen/2);
    swiCopy(&ai_vs_humanMap[0], BG_MAP_RAM_SUB(0), 32*32);


}


void display_start()
{


    TIMER_DATA(0) = (TIMER_FREQ_1024(1));
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    irqSet(IRQ_TIMER0, &ISR_TIMER0);
    irqEnable(IRQ_TIMER0);

    // Switch backgrounds to palettes
    init_main_screen();
    draw_bg_main_screen();
    draw_start_screen();
    delay(2000000);


    draw_part1();
    // Print instructions on top screen
    delay(2000000);
    audio_ufo();
    delay(5000000);
    int bg3_h = 0;
    int bg3_v = -140;
    REG_BG3HOFS_SUB = bg3_h;
    REG_BG3VOFS_SUB = bg3_v;
    swiCopy(&aliensMap[32*48], BG_MAP_RAM_SUB(3), 32*7);


    //swiCopy(start_topBitmap, BG_BMP_RAM(0), start_topBitmapLen/2);
    //swiCopy(start_topPal, BG_PALETTE, start_topPalLen/2);

}