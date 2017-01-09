/*
 * ufo_palet.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the palet ufo movements
 */

#ifndef UFO_PALET_H_
#define UFO_PALET_H_

void ufo_init();
void ufo_step(u8 dir);

extern int ufo_pos_y;						// Pos of the UFO
extern u16* sprite_gfx;						// Handle to palet ufo

#endif /* UFO_PALET_H_ */
