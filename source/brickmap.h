/*
 * brickmap.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the brickmap
 */

#ifndef BRICKMAP_H_
#define BRICKMAP_H_

#include "constants.h"

void brickmap_init();
void brickmap_redraw();
u16 brickmap_check_killed_row(u8 row);
int  brickmap_add_rows(u8 nb);

extern brick_t brickmap[MAX_ROWS][NB_COLS];		// Map of the Mars bricks

#endif /* BRICKMAP_H_ */
