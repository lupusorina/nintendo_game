/*
 * constants.h
 *
 *  Created on: Jan 6, 2017
 *      Author: tardyantoine
 *
 *      Project constants and params
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <nds.h>

// ===== GAMEPLAY PARAMETERS ===================================================
#define MAX_CNT 3						// Max nb of touches to kill a brick
#define NB_BRICKS_BEFORE_BOMB 8			// Nb bricks to be added before a bomb is added
#define PTS_PER_LVL 15					// Points before level up
#define PTS_PER_TOUCH 1					// Points given by touched brick
#define PTS_PER_LINE 4					// Points given by killed row
#define BALL_SPEED_INC_PER_LVL 0.25f	// Speed increment of the ball by level
#define PENALTY_ROWS 2					// Rows added everytime the ball touches the ground
#define BRICK_H 10						// Brick height in pixels
#define BRICK_W 28						// Brick width in pixels
#define MAX_X_ROWS 145					// Limit line for the brickmap, separates low zone and brickmap zone, crossing = NEUROTOXIN!
#define MARGIN  28.0f					// Margin in pixel between the wall and the brickmap
#define NB_ROWS_INIT MAX_ROWS-3			// Last number defines how many empty rows are at init
#define TICKS_BEFORE_RESTART 12			// Nb of ticks at 4 Hz before restart (12 == 3 sec)

// Ball
#define BALL_COLOR		0b1111111111111111 	// Color
#define BALL_RAD		3					// Radius in pixels
#define BALL_X_INIT		170					// Initial x position
#define BALL_Y_INIT		125					// Initial y position
#define BALL_ANGLE_INIT	110					// Initial angle
#define STEP_INIT		1.5f 				// Init step length in pixel of one ball movement = init speed

// UFO
#define UFO_POS_X_MARS  180					// Position x of the palet on Mars
#define UFO_POS_X_EARTH	180					// Position x of the palet on Earth
#define UFO_POS_Y_INIT	100					// Initial y position of palet in pixels
#define UFO_STEP		2.0f				// Step length of palet == palet speed
#define BOTTOM_ROW		185.0f				// Ground level in pixels
#define DELTA_ANGLE_MAX	40.0f				// Maximal angular delta given by the palet to the ball angle
#define ANGLE_MAX		150.0f				// Maximal angle of the ball after bounce
#define ANGLE_MIN		30.0f				// Minimal angle of the ball after bounce

// ===== STRUCTURES ============================================================
typedef struct{			// Brick structure
    int  	type;		// Type standard or vertical bomb
    int 	cnt;		// Counter == nb hits before brick is killed
}brick_t;

typedef struct{			// Ball structure
    u16		color;		// Color
    u8 		r; 			// Radius in pixels
    float 	step;		// Step size in pixels == speed
    float 	x;			// Position x [pix]
    float 	y;			// Position y [pix]
    float 	x_prev;		// Previous position x for erase [pix]
    float 	y_prev;		// Previous position y for erase [pix]
    float 	angle;		// Angle direction, trigonometric in degrees
}ball_t;

typedef struct{			// Player structure
    int		score;		// Current score of player
    u8 		level;		// Current level of player
}player_t;


// ===== Colors ================================================================
#define BRICK_COLOR_5 	0b1000000001111111
#define BRICK_COLOR_4 	0b1000000001111000
#define BRICK_COLOR_3 	0b1000000011111111
#define BRICK_COLOR_2 	0b1000000000011000
#define BRICK_COLOR_1 	0b1000000000010000
#define BLACK_COLOR 	0b1000000000000000
#define MARS_BG_COLOR 	0b1000000111111111
#define EARTH_BG_COLOR 	0b1111110000000000
#define BLUE_COLOR 		0b1111110000000000
#define ORANGE_COLOR 	0b1000000111111111
#define BORDER_COLOR 	0b1000000000000000
#define BOMB_COLOR_1	0b1000001111100000
#define BOMB_COLOR_2	0b1011110000011111
#define SCORE_COLOR 	0b1000001111100000
#define COLOR_LOSES  	0b1000000000011111
#define COLOR_WINS 		0b1000001111100000


// ===== UTILS CONSTANTS =======================================================
#define NONE			0
#define RIGHT			1
#define LEFT			2
#define HALF_UFO_W		32.0f
#define LOST 			-1
#define NOT_LOST 		-2
#define GFX_MARS 		((u16*)BG_GFX)			// Gfx pointer of Mars
#define GFX_EARTH 		((u16*)BG_GFX_SUB)		// Gfx pointer of Earth
#define TYPE_MARS 		0
#define TYPE_EARTH 		1
#define LEFT_WALL 		8.0f
#define MAX_ROWS 		((int)((MAX_X_ROWS-MARGIN)/BRICK_H))
#define LIMIT_ROW  		(int)MARGIN+(MAX_ROWS*BRICK_H)
#define NB_COLS 		(int)((SCREEN_WIDTH-2*MARGIN-LEFT_WALL)/BRICK_W)
#define BTYPE_STD 		0
#define BTYPE_BOMB 		1
#define NO_SHOCK 		-1
#define RESULT_BOMB		-2
#define TIMER_LOST 		0
#define TIMER_BOMB 		1
#define TIMER_OFF 		2

#endif /* CONSTANTS_H_ */
