/*
 * ufo_palet.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the palet ufo movements
 */

#ifndef UFO_PALET_H_
#define UFO_PALET_H_

// ===== EXTERN GLOBAL VARS ====================================================
extern int ufo_pos_y_mars;						// Pos of the UFO
extern u16* sprite_gfx_mars;					// Handle to palet ufo
extern int ufo_pos_y_earth;						// Pos of the UFO
extern u16* sprite_gfx_earth;					// Handle to palet ufo
extern bool AI;									// Playing mode

// ===== UFO PROTOTYPES ========================================================
void ufo_init_mars();							// Init Mars palet
void ufo_step_mars(u8 dir);						// Move Mars palet
void ufo_init_earth();							// Init Earth palet
void ufo_step_earth(u8 dir);					// Move Earth palet

#endif /* UFO_PALET_H_ */
