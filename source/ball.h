/*
 * ball.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the ball movements
 */

#ifndef BALL_H_
#define BALL_H_

#include "constants.h"

void ball_init();
void ball_redraw();
void ball_move();
void ball_check_ufo_shock();
void ball_check_wall_shock();
int ball_check_brick_shock();
void ball_reinit();
bool ball_check_pos_low();

extern int ufo_pos_y;							// Pos of the UFO
extern brick_t brickmap[MAX_ROWS][NB_COLS];		// Map of the Mars bricks

#endif /* BALL_H_ */
