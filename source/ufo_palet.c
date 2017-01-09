/*
 * ufo_palet.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the palet ufo movements
 */

#include <nds.h>
#include "constants.h"
#include "ufo_palet.h"
#include "../data/ufo.h"

// Update the position of the palet
void update_ufo_pos()
{
	// Set pos
	oamSet(&oamMain, 0, ufo_pos_y, UFO_POS_X, 0,0,SpriteSize_64x32,SpriteColorFormat_256Color,sprite_gfx,-1,false,false,false,false,false);
	// Display sprite
	oamUpdate(&oamMain);
}

// Step the UFO sideways
void ufo_step(u8 dir)
{
	if (dir == LEFT){
		if (ufo_pos_y < SCREEN_WIDTH-1-64+UFO_STEP)
			ufo_pos_y += UFO_STEP;
	}
	else if (dir == RIGHT){
		if (ufo_pos_y > -UFO_STEP)
			ufo_pos_y -= UFO_STEP;
	}
	else
		return; // OPTI: Save the update pos
	update_ufo_pos();
}

// Init ufo palet
void ufo_init()
{
	// Palet sprite bank
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	// Init sprite manager and allocate gfx
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	sprite_gfx = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_256Color);
	ufo_pos_y = UFO_POS_Y_INIT;

	// Copy sprite
	swiCopy(ufoPal, SPRITE_PALETTE, ufoPalLen/2);
	swiCopy(ufoTiles, sprite_gfx, ufoTilesLen/2);

	update_ufo_pos();
}
