/*
 * ball.h
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the ball movements
 */

#ifndef BALL_H_
#define BALL_H_

#include "constants.h"

// ===== EXTERN AND GLOBAL VARS ================================================
extern int ufo_pos_y_mars;							// Pos of the UFO on Mars
extern int ufo_pos_y_earth;							// Pos of the UFO on Earth
extern brick_t brickmap[MAX_ROWS][NB_COLS][2];		// Maps of the bricks
extern player_t mars_player;						// Mars player
extern player_t earth_player;						// Earth player
extern bool AI;										// Playing mode
extern bool bombed_rows_mars[MAX_ROWS];				// Array of rows killed by vertical bomb on Mars
extern bool bombed_rows_earth[MAX_ROWS];			// Array of rows killed by vertical bomb on Earth
extern ball_t ball_mars;							// Mars ball

// ===== BALL PROTOTYPES =======================================================
// Ball fucntions, u8 type is either TYPE_MARS or TYPE_EARTH
void ball_init(u8 type);				// Init the ball
void ball_redraw(u8 type);				// Redraw the ball
void ball_move(u8 type);				// Ball makes a step
bool ball_check_ufo_shock(u8 type);		// Check if bounce on palet
void ball_check_wall_shock(u8 type);	// Check if bounce on wall
int ball_check_brick_shock(u8 type);	// Check if bounce on brick
void ball_reinit(u8 type);				// Reinit ball
bool ball_check_pos_low(u8 type);		// Check if ball is low enough to add rows
void ball_inc_speed(u8 type);			// Increment ball speed

#endif /* BALL_H_ */
