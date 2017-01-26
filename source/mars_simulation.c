/*
 * mars_simulation.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the simulation on Mars, interface with the main
 */

#include <nds.h>
#include "mars_simulation.h"
#include "math.h"
#include "background.h"
#include "ball.h"
#include "ufo_palet.h"
#include "brickmap.h"

// ===== GLOBAL VARS ===========================================================
brick_t brickmap_mars[MAX_ROWS][NB_COLS];	// Maps of the bricks
u16* sprite_gfx_mars;						// Handle to palet ufo
int ufo_pos_y_mars;							// Pos of the UFO
bool bombed_rows_mars[MAX_ROWS];			// Bombed rows array
ball_t ball_mars;							// Ball struct for Mars

// ===== MARS SIM IMPLEMENTATIONS ==============================================
// Draws the score on Mars
void mars_draw_score()
{
	int row,col;
	if(AI){
		for(row=0 ; row<SCREEN_HEIGHT ; ++row){
			for(col=0 ; col<LEFT_WALL ; ++col){
				if(row>(int)(SCREEN_HEIGHT-(mars_player.score*SCREEN_HEIGHT/PTS_PER_LVL)) && col>1 && col < LEFT_WALL-2 && row<SCREEN_HEIGHT-2 && row>1)
					GFX_MARS[row*SCREEN_WIDTH + col] = SCORE_COLOR;
				else
					GFX_MARS[row*SCREEN_WIDTH + col] = BLACK_COLOR;
			}
		}
	}
	else{
		for(row=0 ; row<SCREEN_HEIGHT ; ++row){
			for(col=SCREEN_WIDTH-1-LEFT_WALL ; col<SCREEN_WIDTH; ++col){
				if(row<SCREEN_HEIGHT-1-(int)(SCREEN_HEIGHT-(mars_player.score*SCREEN_HEIGHT/PTS_PER_LVL)) && col>SCREEN_WIDTH-LEFT_WALL && col < SCREEN_WIDTH-2 && row<SCREEN_HEIGHT-2 && row>1)
					GFX_MARS[row*SCREEN_WIDTH + col] = SCORE_COLOR;
				else
					GFX_MARS[row*SCREEN_WIDTH + col] = BLACK_COLOR;
			}
		}
	}

}

// Check the Mars score for level up
void mars_check_score()
{
	if(mars_player.score >= PTS_PER_LVL){	// Lvl up
		mars_player.level++;
		mars_player.score = 0;
		ball_inc_speed(TYPE_MARS);
	}
}

// Simulation loop step
int	mars_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added, bool* bool_mars_lost)
{
	// If lines to add by earth, add them when ball is low
	if (lines_to_add > 0){
		if (ball_check_pos_low(TYPE_MARS)){
			*bool_lines_added = true;
			if (brickmap_add_rows(lines_to_add,TYPE_MARS) == LOST){ // If line overflow, LOST
				*bool_mars_lost = true;
				return LOST;
			}
			brickmap_redraw(TYPE_MARS);
		}
	}

	ufo_step_mars(dir);
	ball_move(TYPE_MARS);

	if (ball_check_ufo_shock(TYPE_MARS) == false){	// If ball touched the ground, add line
		if (brickmap_add_rows(PENALTY_ROWS,TYPE_MARS) == LOST){ // If line overflow, LOST
			*bool_mars_lost = true;
			return LOST;
		}
		brickmap_redraw(TYPE_MARS);
	}
	ball_check_wall_shock(TYPE_MARS);

	// Check for bricks bounces, and if lines to add to earth
	int result = ball_check_brick_shock(TYPE_MARS);
	if (result != NO_SHOCK){
		if(result == RESULT_BOMB){
			lines_to_add = brickmap_check_killed_row_bomb(TYPE_MARS);
		}
		else
			lines_to_add = brickmap_check_killed_row(result,TYPE_MARS);
		mars_player.score += PTS_PER_LINE*lines_to_add;
		mars_check_score();
		mars_draw_score();
		brickmap_redraw(TYPE_MARS);
	}
	else
		lines_to_add = 0;

	ball_redraw(TYPE_MARS);
	return lines_to_add;
}

// Init Mars player
void mars_init_player()
{
	mars_player.score = 0;
	mars_player.level = 1;
}

// Restart the mars side
void mars_restart()
{
    mars_init_bg();
	ball_reinit(TYPE_MARS);
	brickmap_init(TYPE_MARS);
	ufo_init_mars();
	mars_init_player();
	mars_draw_score();
}

// Start the mars side
void mars_start()
{
    mars_init_bg();
	brickmap_init(TYPE_MARS);
	ball_init(TYPE_MARS);
	ufo_init_mars();
	mars_init_player();
	mars_draw_score();
}

// Call when Mars player lost
void mars_loses()
{
	u16 row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_MARS[row*SCREEN_WIDTH + col] = COLOR_LOSES;
		}
	}
}

// Call when Mars player lost
void mars_wins()
{
	u16 row, col;
	for(row=0 ; row<SCREEN_HEIGHT ; ++row){
		for(col=0 ; col<SCREEN_WIDTH ; ++col){
			GFX_MARS[row*SCREEN_WIDTH + col] = COLOR_WINS;
		}
	}
}

// AI plays, tries to keep palet under ball (not that smart, are you still there?)
u8 mars_ai_plays()
{
	float bounce_offset = ball_mars.y - (float)((float)ufo_pos_y_mars+(float)HALF_UFO_W);
	if(bounce_offset < 0.0f)
		return RIGHT;
	else
		return LEFT;
}

