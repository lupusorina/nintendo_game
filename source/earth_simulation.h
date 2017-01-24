/*
 * earth_simulation.h
 *
 *  Created on: Jan 15, 2017
 *      Author: tardyantoine
 */

#ifndef EARTH_SIMULATION_H_
#define EARTH_SIMULATION_H_

#include "constants.h"

void 	earth_start();
void 	earth_restart();
int		earth_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added, bool* bool_earth_lost);
void 	earth_loses();
void 	earth_wins();
void 	redraw();

extern player_t earth_player;
extern u8 bomb_color;

#endif /* EARTH_SIMULATION_H_ */
