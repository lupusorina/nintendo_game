/*
 * background.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the BG
 */

#include <nds.h>
#include "constants.h"
#include "../data/cosmos2.h"
#include "background_pic.h"

// Init the BG
void mars_init_bg()
{
	// Init ram
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE ;//| DISPLAY_BG3_ACTIVE;

    // Initialize Background
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256 ;//| BG_PRIORITY_0 | BG_WRAP_ON;
	//BGCTRL[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(26) | BG_TILE_BASE(0) | BG_PRIORITY_1;
		//Background configuration
	//BGCTRL[3] = BG_MAP_BASE(0) | BgSize_B8_256x256| BG_PRIORITY_1;
	//AFfine Matrix
		bgTransform[3]->xdx = 256;
		bgTransform[3]->ydy = 256;
		bgTransform[3]->xdy = 0;
		bgTransform[3]->ydx = 0;
		bgTransform[3]->dy = 0;
		bgTransform[3]->dx = 0;

	BG_PALETTE[0] = 	0b1000001111100000;
	BG_PALETTE[1] = 	0b1000011111111111;
	BG_PALETTE[2] =  	0b1000000000111111;
	BG_PALETTE[3] =  	0b1000000000111000;
	BG_PALETTE[4] =  	0b1000000000011000;
	BG_PALETTE[5] =  	0b1000000000001111;
	BG_PALETTE[6] =  	0b1000000000000111;
	BG_PALETTE[7] =  	0b0000000000000000;
	BG_PALETTE[8] =  	0b1000000011111111;
	BG_PALETTE[9] =  	0b1111110000000000;
	BG_PALETTE[10] =  	0b1111110000000000;
	BG_PALETTE[11] =  	0b1000000111111111;
	BG_PALETTE[12] =  	0b1000000000000000;
	BG_PALETTE[13] =  	0b1000001111100000;
	BG_PALETTE[14] =	0b1000000000011111;
	BG_PALETTE[15] =	0b1000001111100000;
	BG_PALETTE[16] =	0b1111111111111111;


    // Affine Marix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;

    //Copy of the palette and the bitmap
		//dmaCopy(background_picBitmap, BG_MAP_RAM(0), background_picBitmapLen);
		//dmaCopy(background_picPal, BG_PALETTE, background_picPalLen);

	/*swiCopy(background_picTiles, BG_TILE_RAM(0), background_picTilesLen);
	swiCopy(background_picMap, BG_MAP_RAM(26), background_picMapLen);
	swiCopy(background_picPal, BG_PALETTE, background_picPalLen);
*/
	//BG_PALETTE[100] =  	0b1000000111111111;
	//BG_PALETTE[101] =  	0b1111110000000000;

    // Fill BG
    int row, col;
    for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_MARS[row*SCREEN_WIDTH + col] = MARS_BG_COLOR;
		}
	}
}

void earth_init_bg()
{
	// Init ram
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;

    // Initialize Background
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

    // Affine Marix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;


	BG_PALETTE_SUB[0] = 	0b1000001111100000;
	BG_PALETTE_SUB[1] = 	0b1000011111111111;
	BG_PALETTE_SUB[2] =  	0b1000000000111111;
	BG_PALETTE_SUB[3] =  	0b1000000000111000;
	BG_PALETTE_SUB[4] =  	0b1000000000011000;
	BG_PALETTE_SUB[5] =  	0b1000000000001111;
	BG_PALETTE_SUB[6] =  	0b1000000000000111;
	BG_PALETTE_SUB[7] =  	0b0000000000000000;
	BG_PALETTE_SUB[8] =  	0b1000000111111111;
	BG_PALETTE_SUB[9] =  	0b1111110000000000;
	BG_PALETTE_SUB[10] =  	0b1111110000000000;
	BG_PALETTE_SUB[11] =  	0b1000000111111111;
	BG_PALETTE_SUB[12] =  	0b1000000000000000;
	BG_PALETTE_SUB[13] =  	0b1000001111100000;
	BG_PALETTE_SUB[14] =	0b1000000000011111;
	BG_PALETTE_SUB[15] =	0b1000001111100000;
	BG_PALETTE_SUB[16] =	0b1111111111111111;

    int row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_EARTH[row*SCREEN_WIDTH + col] = EARTH_BG_COLOR;
		}
	}
}

