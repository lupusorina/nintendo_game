/*
 * constants.h
 *
 *  Created on: Jan 6, 2017
 *      Author: tardyantoine
 *      Project constants and params
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <nds.h>

// Game
#define LOST -1
#define NOT_LOST -2

// Brickmap
#define BRICK_H 10
#define BRICK_W 60
#define MAX_X_ROWS 145
#define MAX_ROWS (int)(MAX_X_ROWS-MARGIN)/BRICK_H
#define NB_ROWS_INIT MAX_ROWS-5
#define NB_COLS (int)((SCREEN_WIDTH - 2*MARGIN)/BRICK_W)
#define MARGIN  24.0f

typedef struct{
    int  	type;		// Std, explosive, etc...
    int 	cnt;		// Counter until 0 is disappeared
}brick_t;

// Bricks
#define BRICK_COLOR_3 	0b1000000000011111
#define BRICK_COLOR_2 	0b1000000000011100
#define BRICK_COLOR_1 	0b1000000000010000
#define BLACK_COLOR 	0b0000000000000000
#define BORDER_COLOR 	0b1111110000000000
#define BTYPE_STD 		0
#define BTYPE_HOR 		1
#define BTYPE_VER 		2
#define NO_SHOCK 		-1

// Ball
#define BALL_COLOR		0b1111111111111111
#define BALL_RAD		3
#define BALL_X_INIT		170
#define BALL_Y_INIT		125
#define BALL_ANGLE_INIT	120
#define STEP			2 	// Step length in pixel of one ball movement

typedef struct{
    u16		color;
    u8 		r; 			// Radius in pixels
    float 	x;
    float 	y;
    float 	x_prev;
    float 	y_prev;
    float 	angle;		// Angle direction, trigonometric in degrees
}ball_t;

// UFO
#define UFO_POS_X 		180
#define UFO_POS_Y_INIT	100
#define UFO_STEP		3.0f
#define NONE			0
#define RIGHT			1
#define LEFT			2
#define BOTTOM_ROW		185.0f
#define DELTA_ANGLE_MAX	40.0f
#define ANGLE_MAX		150.0f
#define ANGLE_MIN		30.0f
#define HALF_UFO_W		32.0f

#endif /* CONSTANTS_H_ */
