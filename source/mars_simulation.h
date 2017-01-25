/*
 * mars_simulation.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the simulation on Mars, interface with the main
 */

#ifndef MARS_SIMULATION_H_
#define MARS_SIMULATION_H_

#include "constants.h"

void 	mars_start();
void 	mars_restart();
int		mars_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added, bool* bool_mars_lost);
void 	mars_loses();
void 	mars_wins();
u8	 	mars_ai_plays();

extern brick_t brickmap[MAX_ROWS][NB_COLS][2];		// Maps of the bricks
ball_t ball_mars;							// Ball struct
extern player_t mars_player;
extern bool AI;

#endif /* MARS_SIMULATION_H_ */
