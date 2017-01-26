/*
 * ufo_palet.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the palet ufo movements
 */

#include <nds.h>
#include "constants.h"
#include "ufo_palet.h"
#include "ufo.h"

// ===== UFO IMPLEMENTATIONS ===================================================
// Update the position of the palet
void update_ufo_pos_mars()
{
	// Set pos
	if(AI)	// If AI
		oamSet(&oamMain, 0, ufo_pos_y_mars, UFO_POS_X_MARS, 0,0,SpriteSize_64x32,SpriteColorFormat_256Color,sprite_gfx_mars,-1,false,false,false,false,false);
	else{	// else, mirror screen
		oamSet(&oamMain, 0, SCREEN_WIDTH -1 -64 - ufo_pos_y_mars, SCREEN_HEIGHT -1 -32 - UFO_POS_X_MARS, 0,0,SpriteSize_64x32,SpriteColorFormat_256Color,sprite_gfx_mars,-1,false,false,true,true,false);
	}
		// Display sprite
	oamUpdate(&oamMain);
}

// Update Earth UFO pos
void update_ufo_pos_earth()
{
	// Set pos
	oamSet(&oamSub, 0, ufo_pos_y_earth, UFO_POS_X_EARTH, 0,0,SpriteSize_64x32,SpriteColorFormat_256Color,sprite_gfx_earth,-1,false,false,false,false,false);
	// Display sprite
	oamUpdate(&oamSub);
}

// Step the UFO sideways
void ufo_step_mars(u8 dir)
{
	if (dir == LEFT){
		if (ufo_pos_y_mars < SCREEN_WIDTH-1-64+UFO_STEP)
			ufo_pos_y_mars += UFO_STEP;
	}
	else if (dir == RIGHT){
		if (ufo_pos_y_mars > -UFO_STEP+LEFT_WALL)
			ufo_pos_y_mars -= UFO_STEP;
	}
	else
		return; // OPTI: Save the update pos
	update_ufo_pos_mars();
}

// Step the UFO sideways
void ufo_step_earth(u8 dir)
{
	if (dir == LEFT){
		if (ufo_pos_y_earth < SCREEN_WIDTH-1-64+UFO_STEP)
			ufo_pos_y_earth += UFO_STEP;
	}
	else if (dir == RIGHT){
		if (ufo_pos_y_earth > -UFO_STEP+LEFT_WALL)
			ufo_pos_y_earth -= UFO_STEP;
	}
	else
		return; // OPTI: Save the update pos
	update_ufo_pos_earth();
}

// Init ufo palet
void ufo_init_mars()
{
	// Palet sprite bank
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	// Init sprite manager and allocate gfx
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	sprite_gfx_mars = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_256Color);
	ufo_pos_y_mars = UFO_POS_Y_INIT;

	// Copy sprite
	swiCopy(ufoPal, SPRITE_PALETTE, ufoPalLen/2);
	swiCopy(ufoTiles, sprite_gfx_mars, ufoTilesLen/2);

	update_ufo_pos_mars();
}

// Init ufo palet
void ufo_init_earth()
{
	// Palet sprite bank
	VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;

	// Init sprite manager and allocate gfx
	oamInit(&oamSub, SpriteMapping_1D_32, false);
	sprite_gfx_earth = oamAllocateGfx(&oamSub, SpriteSize_64x32, SpriteColorFormat_256Color);
	ufo_pos_y_earth = UFO_POS_Y_INIT;

	// Copy sprite
	swiCopy(ufoPal, SPRITE_PALETTE_SUB, ufoPalLen/2);
	swiCopy(ufoTiles, sprite_gfx_earth, ufoTilesLen/2);

	update_ufo_pos_earth();
}
