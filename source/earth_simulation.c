/*
 * earth_simulation.c
 *
 *  Created on: Jan 15, 2017
 *      Author: tardyantoine
 *
  *      Handles the simulation on Earth, interface with the main
 */

#include <nds.h>
#include "earth_simulation.h"
#include "math.h"
#include "constants.h"
#include "background.h"
#include "ball.h"
#include "ufo_palet.h"
#include "brickmap.h"

// ===== GLOBAL VARS ===========================================================
brick_t brickmap_earth[MAX_ROWS][NB_COLS];	// Maps of the bricks
u16* sprite_gfx_earth;						// Handle to palet ufo
int ufo_pos_y_earth;						// Pos of the UFO
bool bombed_rows_earth[MAX_ROWS];			// Bombed rows array

// ===== EARTH SIM IMPLEMENTATIONS =============================================
// Draw score on Earth
void earth_draw_score()
{
	int row,col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<LEFT_WALL ; ++col){
			if(row>(int)(SCREEN_HEIGHT-(earth_player.score*SCREEN_HEIGHT/PTS_PER_LVL)) && col>1 && col < LEFT_WALL-2 && row<SCREEN_HEIGHT-2 && row>1)
				GFX_EARTH[row*SCREEN_WIDTH + col] = SCORE_COLOR;
			else
				GFX_EARTH[row*SCREEN_WIDTH + col] = BLACK_COLOR;
		}
	}
}

// Check score for level up
void earth_check_score()
{
	if(earth_player.score >= PTS_PER_LVL){	// Lvl up
		earth_player.level++;
		earth_player.score = 0;
		ball_inc_speed(TYPE_EARTH);
	}
}

// Simulation loop step
int	earth_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added, bool* bool_earth_lost)
{
	// If lines to add by earth, add them when ball is low
	if (lines_to_add > 0){
		if (ball_check_pos_low(TYPE_EARTH)){
			*bool_lines_added = true;
			if (brickmap_add_rows(lines_to_add,TYPE_EARTH) == LOST){ // If line overflow, LOST
				*bool_earth_lost = true;
				return LOST;
			}
			brickmap_redraw(TYPE_EARTH);
		}
	}

	// Move ball and ufo
	ufo_step_earth(dir);
	ball_move(TYPE_EARTH);

	if (ball_check_ufo_shock(TYPE_EARTH) == false){	// If ball touched the ground, add line
		if (brickmap_add_rows(PENALTY_ROWS,TYPE_EARTH) == LOST){ // If line overflow, LOST
			*bool_earth_lost = true;
			return LOST;
		}
		brickmap_redraw(TYPE_EARTH);
	}

	ball_check_wall_shock(TYPE_EARTH);

	// Check for bricks bounces, and if lines to add to earth
	int result = ball_check_brick_shock(TYPE_EARTH);
	if (result != NO_SHOCK){
		if(result == RESULT_BOMB){
			lines_to_add = brickmap_check_killed_row_bomb(TYPE_EARTH);
		}
		else
			lines_to_add = brickmap_check_killed_row(result,TYPE_EARTH);
		earth_player.score += PTS_PER_LINE*lines_to_add;
		earth_check_score();
		earth_draw_score();
		brickmap_redraw(TYPE_EARTH);
	}
	else
		lines_to_add = 0;

	ball_redraw(TYPE_EARTH);
	return lines_to_add;
}

// Init player
void earth_init_player()
{
	earth_player.score = 0;
	earth_player.level = 1;
}

// Restart the earth side
void earth_restart()
{
	earth_init_bg();
	ball_reinit(TYPE_EARTH);
	brickmap_init(TYPE_EARTH);
	ufo_init_earth();
	earth_init_player();
	earth_draw_score();
}

// Start the earth side
void earth_start()
{
	earth_init_bg();
	brickmap_init(TYPE_EARTH);
	ball_init(TYPE_EARTH);
	ufo_init_earth();
	earth_init_player();
	earth_draw_score();
}

// Call when earth player lost
void earth_loses()
{
	u16 row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_EARTH[row*SCREEN_WIDTH + col] = COLOR_LOSES;
		}
	}
}

// Call when earth player lost
void earth_wins()
{
	u16 row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_EARTH[row*SCREEN_WIDTH + col] = COLOR_WINS;
		}
	}
}

// Redraw the bombs for mars and earth
void redraw()
{
	brickmap_redraw_bombs(TYPE_EARTH);
	brickmap_redraw_bombs(TYPE_MARS);
}


