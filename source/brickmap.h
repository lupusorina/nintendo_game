/*
 * brickmap.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the brickmap
 */

#ifndef BRICKMAP_H_
#define BRICKMAP_H_

#include "constants.h"

// ===== EXTERN GLOBAL VARS ====================================================
extern brick_t brickmap[MAX_ROWS][NB_COLS][2];	// Maps of the bricks
extern player_t earth_player;					// Earth player
extern player_t mars_player;					// Mars player
extern bool AI;									// Playing mode
extern bool bombed_rows_mars[MAX_ROWS];			// Array of rows killed by vertical bomb on Mars
extern bool bombed_rows_earth[MAX_ROWS];		// Array of rows killed by vertical bomb on Earth
extern u16 bomb_color;							// Current bomb color

// ===== BRICKMAP FUNC PROTOTYPES ==============================================
void brickmap_init(u8 type);					// Init brickmap
void brickmap_redraw(u8 type);					// Redraw brickmap
u16 brickmap_check_killed_row(u8 row,u8 type);	// Check if a row was killed by ball
u16 brickmap_check_killed_row_bomb(u8 type);	// Check if a row was kille by bomb
int  brickmap_add_rows(u8 nb,u8 type);			// Add rows to the brickmap
void brickmap_redraw_bombs(u8 type);			// Redraw the bombs

#endif /* BRICKMAP_H_ */
