/*
 * mars_simulation.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the simulation on Mars, interface with the main
 */

#include <nds.h>
#include <stdio.h>
#include "mars_simulation.h"
#include "math.h"
#include "constants.h"
#include "background.h"
#include "ball.h"
#include "ufo_palet.h"
#include "brickmap.h"

// MARS PLAYER SIDE

// Global vars
brick_t brickmap[MAX_ROWS][NB_COLS];	// Map of the Mars bricks
u16* sprite_gfx;						// Handle to palet ufo
int ufo_pos_y;							// Pos of the UFO

// Simulation loop step
int mars_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added)
{
	if (lines_to_add > 0){
		if (ball_check_pos_low()){
			*bool_lines_added = true;
			if (brickmap_add_rows(lines_to_add) == LOST)
				return LOST;
			brickmap_redraw();
		}
	}
	ufo_step(dir);
	ball_move();
	ball_check_ufo_shock();
	ball_check_wall_shock();
	int result = ball_check_brick_shock();
	if (result != NO_SHOCK){
		lines_to_add = brickmap_check_killed_row(result);
		brickmap_redraw();
	}
	else
		lines_to_add = 0;

	ball_redraw();
	return lines_to_add;
}

// Restart the mars side
void mars_restart()
{
	ball_reinit();
	brickmap_init();
	ufo_init();
}

// Start the mars side
void mars_start()
{
    mars_init_bg();
	brickmap_init();
	ball_init();
	ufo_init();
}

