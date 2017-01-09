/*
 * mars_simulation.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the simulation on Mars, interface with the main
 */

#ifndef MARS_SIMULATION_H_
#define MARS_SIMULATION_H_

void 	mars_start();
void 	mars_restart();
int		mars_sim_step(u8 dir, u8 lines_to_add, bool* bool_lines_added);

#endif /* MARS_SIMULATION_H_ */
