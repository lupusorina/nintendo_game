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

void ball_init(u8 type);
void ball_redraw(u8 type);
void ball_move(u8 type);
bool ball_check_ufo_shock(u8 type);
void ball_check_wall_shock(u8 type);
int ball_check_brick_shock(u8 type);
void ball_reinit(u8 type);
bool ball_check_pos_low(u8 type);
void ball_inc_speed(u8 type);

extern int ufo_pos_y_mars;							// Pos of the UFO
extern int ufo_pos_y_earth;							// Pos of the UFO
extern brick_t brickmap[MAX_ROWS][NB_COLS][2];		// Maps of the bricks
extern player_t mars_player;
extern player_t earth_player;
extern bool AI;
extern bool bombed_rows_mars[MAX_ROWS];
extern bool bombed_rows_earth[MAX_ROWS];

#endif /* BALL_H_ */
