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
#define NB_BRICKS_BEFORE_BOMB 4
#define PTS_PER_LVL 10
#define PTS_PER_TOUCH 2
#define PTS_PER_LINE 4
#define BALL_SPEED_INC_PER_LVL 0.2f
#define LOST -1
#define NOT_LOST -2
#define PENALTY_ROWS 2
#define GFX_MARS ((u8*)BG_MAP_RAM(0))
#define GFX_EARTH ((u8*)BG_GFX_SUB)
#define TYPE_MARS 0
#define TYPE_EARTH 1/*
#define X_TO_MARS type*SCREEN_HEIGHT+(2*((type+1)%2)-1)*
#define Y_TO_MARS type*SCREEN_WIDTH+(2*((type+1)%2)-1)*
#define ANGLE_TO_MARS type*180.0f+*/

// Brickmap
#define LEFT_WALL 8.0f
#define BRICK_H 10
#define BRICK_W 60
#define MAX_X_ROWS 145
#define MAX_ROWS ((int)((MAX_X_ROWS-MARGIN)/BRICK_H))
#define LIMIT_ROW  (int)MARGIN+(MAX_ROWS*BRICK_H)
#define NB_ROWS_INIT MAX_ROWS-6
#define NB_COLS (int)((SCREEN_WIDTH-2*MARGIN-LEFT_WALL)/BRICK_W)
#define MARGIN  28.0f

typedef struct{
    int  	type;		// Std, explosive, etc...
    int 	cnt;		// Counter until 0 is disappeared
}brick_t;

// Bricks
#define BOMB_COLOR_1	0
#define BOMB_COLOR_2	1
#define BRICK_COLOR_5 	2
#define BRICK_COLOR_4 	3
#define BRICK_COLOR_3 	4
#define BRICK_COLOR_2 	5
#define BRICK_COLOR_1 	6
#define BLACK_COLOR 	7
#define MARS_BG_COLOR 	8
#define EARTH_BG_COLOR 	9
#define BLUE_COLOR 		10
#define ORANGE_COLOR 	11
#define BORDER_COLOR 	12
#define SCORE_COLOR 	13
#define COLOR_LOSES  	14
#define COLOR_WINS 		15
#define BTYPE_STD 		0
#define BTYPE_BOMB 		1
#define NO_SHOCK 		-1
#define RESULT_BOMB		-2

// Ball
#define BALL_COLOR		16
#define BALL_RAD		4
#define BALL_X_INIT		170
#define BALL_Y_INIT		125
#define BALL_ANGLE_INIT	120
#define STEP_INIT		1.5f 	// Step length in pixel of one ball movement

typedef struct{
    u16		color;
    u8 		r; 			// Radius in pixels
    float 	step;
    float 	x;
    float 	y;
    float 	x_prev;
    float 	y_prev;
    float 	angle;		// Angle direction, trigonometric in degrees
}ball_t;

// UFO
#define UFO_POS_X_MARS  180
#define UFO_POS_X_EARTH	180
#define UFO_POS_Y_INIT	100
#define UFO_STEP		2.0f
#define NONE			0
#define RIGHT			1
#define LEFT			2
#define BOTTOM_ROW		185.0f
#define DELTA_ANGLE_MAX	40.0f
#define ANGLE_MAX		150.0f
#define ANGLE_MIN		30.0f
#define HALF_UFO_W		32.0f

typedef struct{
    int		score;
    u8 		level;
}player_t;

#endif /* CONSTANTS_H_ */
