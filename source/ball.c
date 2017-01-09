/*
 * ball.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the ball movements and bounces
 */

#include "ball.h"
#include <nds.h>
#include <stdio.h>
#include "math.h"

ball_t ball;							// Ball struct

// Angles
float rad2deg(float rads){return rads/3.141592654*180.0f;}
float deg2rad(float degs){return degs*3.141592654/180.0f;}
float normalize(float angle)
{
	bool done = false;
	while(!done){
		if (angle < 0)
			angle += 360;
		else if (angle > 360)
			angle -= 360;
		else
			done = true;
	}
	return angle;
}

// Check if the point is within an active brick. If yes returns true and sets brick
bool check_point_vs_brick(float x, float y, int* br_row, int* br_col)
{
	float r =(x-MARGIN)/BRICK_H;
	float c = (y-MARGIN)/BRICK_W;
	bool ret = true;

	// Check if pos is before map
	if (r<0 || c<0)
		ret = false;

	// Use cast to round down
	int row = (int)r;
	int col = (int)c;

	// Check if not in the map or inactive brick
	if (row>=MAX_ROWS || col>=NB_COLS)
		ret = false;
	else if (brickmap[row][col].cnt<1)
		ret = false;

	// Pos valid, send pos
	*br_row = row;
	*br_col= col;
	return ret;
}

void ball_redraw()
{
	int x_draw = round(ball.x_prev);
	int y_draw = round(ball.y_prev);
	int top = x_draw - ball.r;
	int bottom = x_draw + ball.r;
	int left = y_draw - ball.r;
	int right = y_draw + ball.r;
	int i,j;

	// Erase previous ball
	for(i = top; i < bottom; i++){
		for(j = left; j < right; j++){
			BG_GFX[i*SCREEN_WIDTH + j] = BLACK_COLOR;	// Transparent
		}
	}

	x_draw = round(ball.x);
	y_draw = round(ball.y);
	top = x_draw - ball.r;
	bottom = x_draw + ball.r;
	left = y_draw - ball.r;
	right = y_draw + ball.r;

	// Draw new ball
	for(i = top; i < bottom; i++){
		for(j = left; j < right; j++){
			BG_GFX[i*SCREEN_WIDTH + j] = ball.color;	// Rectangle around brick
		}
	}
}

// Init the ball
void ball_init()
{
	ball.color = BALL_COLOR;
	ball.r = BALL_RAD;
	ball.x = BALL_X_INIT;
	ball.y = BALL_Y_INIT;
	ball.x_prev = BALL_X_INIT;
	ball.y_prev = BALL_Y_INIT;
	ball.angle = BALL_ANGLE_INIT;

	ball_redraw();
}

// Reinit the ball
void ball_reinit()
{
	ball.x_prev = ball.x;
	ball.y_prev = ball.y;
	ball.x = BALL_X_INIT;
	ball.y = BALL_Y_INIT;
	ball.angle = BALL_ANGLE_INIT;

	ball_redraw();
}


void ball_move()
{
	// Store previous values of pos
	ball.x_prev = ball.x;
	ball.y_prev = ball.y;

	// Calculate new position
	ball.x -= STEP*sin(deg2rad(ball.angle));
	ball.y += STEP*cos(deg2rad(ball.angle));
}


void ball_check_ufo_shock()
{
	// Check bounce on the bottom
	if (ball.x > BOTTOM_ROW - ball.r){				// Bottom shock
		float bounce_offset = ball.y - (float)(ufo_pos_y+HALF_UFO_W);
		if (abs(bounce_offset) < HALF_UFO_W+ball.r){		// The ufo is there
			ball.angle = (-1.0f)*ball.angle - bounce_offset/(float)(HALF_UFO_W+ball.r)*(float)DELTA_ANGLE_MAX;
			if (normalize(ball.angle) > ANGLE_MAX)
				ball.angle = ANGLE_MAX;
			if (normalize(ball.angle) < ANGLE_MIN)
				ball.angle = ANGLE_MIN;
			ball.x += 2*((float)BOTTOM_ROW-(ball.x+ball.r));
		}
		else{	// Did not catch the ball
			printf("Bwaaah what a loser!\n");
		}
	}
}

void ball_check_wall_shock()
{
	// Check wall bounce
	if (ball.x < ball.r){				// Top shock
		ball.angle *= -1.0f;
		ball.x += 2*(ball.r-ball.x);
	}

	if (ball.y > SCREEN_WIDTH-ball.r){		// Right shock
		ball.angle = 180.0f - ball.angle;
		ball.y -= 2*(ball.y-(SCREEN_WIDTH-ball.r));
	}
	else if (ball.y< ball.r){				// Left shock
		ball.angle = 180.0f - ball.angle;
		ball.y += 2*(ball.r-ball.y);
	}
}

int ball_check_brick_shock()
{
	int br_row = -1;
	int br_col = -1;
	bool shock = false;
	int result = NO_SHOCK;

	// Top corner shock
	if (check_point_vs_brick(ball.x-ball.r , ball.y , &br_row, &br_col)){
		brickmap[br_row][br_col].cnt--;
		ball.angle *= -1.0f;
		ball.x += STEP/2;
		shock = true;
	}
	// Left corner shock
	else if(check_point_vs_brick(ball.x , ball.y-ball.r , &br_row, &br_col)){
		brickmap[br_row][br_col].cnt--;
		ball.angle = 180.0f - ball.angle;
		ball.y += STEP/2;
		shock = true;
	}
	// Bottom corner shock
	else if (check_point_vs_brick(ball.x+ball.r , ball.y , &br_row, &br_col)){
		brickmap[br_row][br_col].cnt--;
		ball.angle *= -1.0f;
		ball.x -= STEP/2;
		shock = true;
	}
	// Right corner shock
	else if(check_point_vs_brick(ball.x , ball.y+ball.r , &br_row, &br_col)){
		brickmap[br_row][br_col].cnt--;
		ball.angle = 180.0f - ball.angle;
		ball.y -= STEP/2;
		shock = true;
	}

	// If shock happened, send row index to know if full row was killed
	if (shock == true)
		result = br_row;

	return result;
}

// Returns true if the ball enough for the lines to be added
bool ball_check_pos_low()
{
	if(ball.x > MAX_X_ROWS){
		return true;
	}
	else{
		return false;
	}
}
