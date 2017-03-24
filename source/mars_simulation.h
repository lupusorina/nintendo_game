/*
 * mars_simulation.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the simulation on Mars, interface with the main
 */

#ifndef MARS_SIMULATION_H_
#define MARS_SIMULATION_H_

#include "constants.h"

// ===== EXTERN GLOBAL VARS ====================================================
extern brick_t brickmap[MAX_ROWS][NB_COLS][2];		// Maps of the bricks
extern player_t mars_player;						// Mars player
extern bool AI;										// Playing mode

// ===== MARS SIM PROTOTYPES ===================================================
void 	mars_start();		// Start
void 	mars_restart();		// Restart

// Sim step. Ret lines to add to Earh, mod lines added bool and tells if Mars lost
int		mars_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added, bool* bool_mars_lost);
void 	mars_loses();		// Lost
void 	mars_wins();		// Won
u8	 	mars_ai_plays();	// AI move if not PvP

#endif /* MARS_SIMULATION_H_ */
