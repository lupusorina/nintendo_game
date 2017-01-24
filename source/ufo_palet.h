/*
 * ufo_palet.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the palet ufo movements
 */

#ifndef UFO_PALET_H_
#define UFO_PALET_H_

void ufo_init_mars();
void ufo_step_mars(u8 dir);

void ufo_init_earth();
void ufo_step_earth(u8 dir);

extern int ufo_pos_y_mars;						// Pos of the UFO
extern u16* sprite_gfx_mars;					// Handle to palet ufo

extern int ufo_pos_y_earth;						// Pos of the UFO
extern u16* sprite_gfx_earth;					// Handle to palet ufo
extern bool AI;

#endif /* UFO_PALET_H_ */
