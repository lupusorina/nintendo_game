/*
 * earth_simulation.h
 *
 *  Created on: Jan 15, 2017
 *      Author: tardyantoine
 *
 *      Simulation, Earth side
 */

#ifndef EARTH_SIMULATION_H_
#define EARTH_SIMULATION_H_

#include "constants.h"

// ===== EXTERN GLOBAL VARS ====================================================
extern player_t earth_player;	// Earth player
extern u16 bomb_color;			// Current bomb color

// ===== EARTH SIM PROTOTYPES ==================================================
void 	earth_start();		// Start
void 	earth_restart();	// Restart

// Sim step. Ret lines to add to mars, mod lines added bool and tells if earth lost
int		earth_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added, bool* bool_earth_lost);
void 	earth_loses();		// Lost
void 	earth_wins();		// Won
void 	redraw();			// Redraw bombs


#endif /* EARTH_SIMULATION_H_ */
