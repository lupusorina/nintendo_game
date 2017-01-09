/*
 * background.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the BG
 */

#include <nds.h>

// Init the BG
void mars_init_bg()
{
	// Init ram
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

    // Initialize Background
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B16_256x256;

    // Affine Marix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;
}

void earth_init_bg()
{
	;

	/* STUB
	// Init ram
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

    // Initialize Background
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B16_256x256;

    // Affine Marix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;*/
}
