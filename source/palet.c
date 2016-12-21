#include "palet.h"
#include <stdlib.h>

u8 tile0[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

u8 middle[64] = {
    240, 240, 240, 240, 240, 240, 240, 240,
    241, 240, 240, 240, 240, 240, 241, 241,
    241, 241, 241, 240, 240, 241, 241, 241,
    241, 241, 241, 241, 241, 241, 241, 241,
    241, 241, 241, 241, 241, 241, 241, 241,
    241, 241, 241, 241, 241, 241, 241, 241,
    241, 241, 241, 241, 241, 241, 241, 241,
    241, 241, 241, 241, 241, 241, 241, 241
};

u8 corner[64] = {
    0,   0,    0,   240,    240,    240,    240,    240,
    0,   0,    241, 241,    240,    240,    241,    241,
    0,   241,  241, 241,    241,    240,    241,    241,
    241, 241,  241, 241,    241,    241,    241,    241,
    241, 241,  241, 241,    241,    241,    241,    241,
    0,   241,  241, 241,    241,    241,    241,    241,
    0,   0,    241, 241,    241,    241,    241,    241,
    0,   0,    0,   241,    241,    241,    241,  241
};

u8 brick_red_style[64];
u8 brick_blue_style[64];
u8 brick_green_style[64];

void color_bricks(){
    int i;
     for (i = 0; i < TILE_SIZE; i++){
        brick_red_style[i] = (rand() % 2) + 243;
        brick_blue_style[i] = (rand() % 2) + 246;
        brick_green_style[i] = (rand() % 2) + 249;
    }
}



void assign_colors(u16* palette_buffer){
    palette_buffer[240] = ARGB16(1,26,0,0);
    palette_buffer[241] = ARGB16(1,28,15,0);

    palette_buffer[243] = ARGB16(1,26,0,0);
    palette_buffer[244] = ARGB16(1,11,0,0);
    palette_buffer[245] = ARGB16(1,26,12,0);

    palette_buffer[246] = ARGB16(1,0,0,10);
    palette_buffer[247] = ARGB16(1,0,0,30);
    palette_buffer[248] = ARGB16(1,0,12,28);

    palette_buffer[249] = ARGB16(1,0,10,0);
    palette_buffer[250] = ARGB16(1,0,30,0);
    palette_buffer[251] = ARGB16(1,12,28,0);
}

void place_paddle_initially(struct sBuf bf){
    int i,j;

    color_bricks();
    dmaCopy(tile0, (u8*)bf.tile_buffer, TILE_SIZE);
    dmaCopy(middle, (u8*)bf.tile_buffer + TILE_SIZE, TILE_SIZE);
    dmaCopy(corner, (u8*)bf.tile_buffer + 2 * TILE_SIZE, TILE_SIZE);
    dmaCopy(brick_red_style, (u8*)bf.tile_buffer + 3 * TILE_SIZE, TILE_SIZE);
    dmaCopy(brick_blue_style, (u8*)bf.tile_buffer + 4 * TILE_SIZE, TILE_SIZE);
    dmaCopy(brick_green_style, (u8*)bf.tile_buffer + 5 * TILE_SIZE, TILE_SIZE);



    assign_colors(bf.palette_buffer);


    int last_row = 23;
    bf.map_buffer[32 * last_row + 11] = 2;
    bf.map_buffer[32 * last_row + 12] = 1;
    bf.map_buffer[32 * last_row + 13] = 1;
    bf.map_buffer[32 * last_row + 14] = 1;
    bf.map_buffer[32 * last_row + 15] = 1;
    bf.map_buffer[32 * last_row + 16] = 1;
    bf.map_buffer[32 * last_row + 17] = 1;
    bf.map_buffer[32 * last_row + 18] = 1;
    bf.map_buffer[32 * last_row + 19] = 2 | MIRROR;

    for (i = 10; i <= 10; i++)
        for(j = 4; j <= 8; j++){
            bf.map_buffer[32 * i + j] = 3;
            bf.map_buffer[32 * i + j + 5] = 4;
            bf.map_buffer[32 * (i + 1) + j + 5] = 3;
            bf.map_buffer[32 * (i + 1) + j] = 4;
            bf.map_buffer[32 * (i + 2) + j + 10] = 3;
            bf.map_buffer[32 * (i + 1) + j + 10] = 4;
            bf.map_buffer[32 * (i + 3) + j + 10] = 5;
            bf.map_buffer[32 * (i + 4) + j + 4] = 5;
        }

}


void move_palet(){
    int i,j;
    u16 keys = ~(REG_KEYINPUT);

    static int delta = 0;

    if (keys == KEY_START)
    {
        for (i = 23; i < 24; i++)
            for (j = 4 + delta; j < 8 + delta ; j++){
                if (j + delta == FRAME_WIDTH) break;
                BG_MAP_RAM_SUB(1)[32 * i + j] = 0;
                BG_MAP_RAM_SUB(1)[32 * i + j - delta - 1] = 0;
            }
        delta++;
    }
}
