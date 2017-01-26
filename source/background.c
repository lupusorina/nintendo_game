/*
 * background.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the BG
 */

#include <nds.h>
#include "constants.h"
#include "start_pic.h"

// Init the BG of Mars
void mars_init_bg()
{
	// Init ram
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D  | DISPLAY_BG2_ACTIVE;

	 // Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	// Initialize Background Main in 16bits bitmap for halfword access
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B16_256x256 ;

    // Fill BG
	int row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_MARS[row*SCREEN_WIDTH + col] = MARS_BG_COLOR;
		}
	}
}

// Init BG of Earth
void earth_init_bg()
{
	// Init ram
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;

    // Initialize Background Sub in 16bits bitmap for halfword access
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B16_256x256;

    // Affine Marix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    int row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_EARTH[row*SCREEN_WIDTH + col] = EARTH_BG_COLOR;
		}
	}
}

