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

void brickmap_init(u8 type);
void brickmap_redraw(u8 type);
u16 brickmap_check_killed_row(u8 row,u8 type);
u16 brickmap_check_killed_row_bomb(u8 type);
int  brickmap_add_rows(u8 nb,u8 type);
void brickmap_redraw_bombs(u8 type);

extern brick_t brickmap[MAX_ROWS][NB_COLS][2];		// Maps of the bricks
extern player_t earth_player;
extern player_t mars_player;
extern bool AI;
extern bool bombed_rows_mars[MAX_ROWS];
extern bool bombed_rows_earth[MAX_ROWS];

#endif /* BRICKMAP_H_ */
