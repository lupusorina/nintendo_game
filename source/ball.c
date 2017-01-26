/*
 * ball.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *
 *      Handles the ball movements and bounces
 */

#include "ball.h"
#include <nds.h>
#include "math.h"

// ===== GLOBAL VARS ===========================================================
ball_t ball_earth;							// Mars ball struct

// ===== BALL FUNC IMPLEMENTATIONS =============================================
// Increment ball speed, type is mars or earth
void ball_inc_speed(u8 type)
{
	if(type == TYPE_MARS)
		ball_mars.step += BALL_SPEED_INC_PER_LVL;
	else
		ball_earth.step += BALL_SPEED_INC_PER_LVL;
}

// Angles utils functions
float rad2deg(float rads){return rads/3.141592654*180.0f;}	// Conversion
float deg2rad(float degs){return degs*3.141592654/180.0f;}	// Conversion

// Normalizes angle between 0 and 360 (trigonometric degrees)
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

// Check if the point (x,y) is within an active brick. If yes returns true and sets brick
bool check_point_vs_brick(float x, float y, int* br_row, int* br_col,u8 type)
{
	// Convert
	float r =(x-MARGIN)/BRICK_H;
	float c = (y-MARGIN-LEFT_WALL)/BRICK_W;
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
	else{
		if(brickmap[row][col][type].cnt<1){
			ret = false;
		}
	}

	// Pos valid, send pos
	*br_row = row;
	*br_col= col;
	return ret;
}

// Draw the dead line on correct screen
void draw_limit_line(u8 type)
{
	u16* gfx = NULL;
	u16 bound = LIMIT_ROW;
	if(type == TYPE_MARS){
		gfx = GFX_MARS;
		if(!AI)
			bound = SCREEN_HEIGHT - bound - 3;
	}
	else
		gfx = GFX_EARTH;
	int i;

	// Dashed black line
	for(i=0 ; i<2*SCREEN_WIDTH ; ++i)
	{
		if(i%8 > 2)
			gfx[bound*SCREEN_WIDTH + i] = BORDER_COLOR;
	}
}

// Ball redraw event
void ball_redraw(u8 type)
{
	// Used as rounded values for painting
	int x_draw,y_draw;
	u8 r;
	u16 color, bg_color;
	u16* graphic_buffer = NULL;

	// Position conversions and type sets
	if(type == TYPE_MARS){
		if(AI){
			x_draw = round(ball_mars.x_prev);
			y_draw = round(ball_mars.y_prev);
		}
		else{
			x_draw = SCREEN_HEIGHT - 1  - round(ball_mars.x_prev);
			y_draw = SCREEN_WIDTH - 1 - round(ball_mars.y_prev);
		}
		r = ball_mars.r;
		graphic_buffer = GFX_MARS;
		color = ball_mars.color;
		bg_color = MARS_BG_COLOR;
	}
	else{
		x_draw = round(ball_earth.x_prev);
		y_draw = round(ball_earth.y_prev);
		r = ball_earth.r;
		graphic_buffer = GFX_EARTH;
		color = ball_earth.color;
		bg_color = EARTH_BG_COLOR;
	}


	int top = x_draw - r;
	int bottom = x_draw + r;
	int left = y_draw - r;
	int right = y_draw + r;
	int i,j;

	// Erase previous ball
	for(i = top; i < bottom; i++){
		for(j = left; j < right; j++){
			graphic_buffer[i*SCREEN_WIDTH + j] = bg_color;	// Transparent
		}
	}
	draw_limit_line(type);

	if(type == TYPE_MARS){
		if(AI){
			x_draw = round(ball_mars.x);
			y_draw = round(ball_mars.y);
		}
		else{
			x_draw = SCREEN_HEIGHT - 1 - round(ball_mars.x);
			y_draw = SCREEN_WIDTH - 1 - round(ball_mars.y);
		}
	}
	else{
		x_draw = round(ball_earth.x);
		y_draw = round(ball_earth.y);
	}

	top = x_draw - r;
	bottom = x_draw + r;
	left = y_draw - r;
	right = y_draw + r;

	// Draw new ball
	for(i = top; i < bottom; i++){
		for(j = left; j < right; j++){
			if((i-x_draw)*(i-x_draw) + (j-y_draw)*(j-y_draw) < r*r)
				graphic_buffer[i*SCREEN_WIDTH + j] = color;	// Rectangle around ball
		}
	}
}

// Init the ball
void ball_init(u8 type)
{
	if(type == TYPE_MARS){
		ball_mars.color = BALL_COLOR;
		ball_mars.r = BALL_RAD;
		ball_mars.x = BALL_X_INIT;
		ball_mars.y = BALL_Y_INIT;
		ball_mars.x_prev = BALL_X_INIT;
		ball_mars.y_prev = BALL_Y_INIT;
		ball_mars.angle = BALL_ANGLE_INIT;
		ball_mars.step = STEP_INIT;
	}
	else{
		ball_earth.color = BALL_COLOR;
		ball_earth.r = BALL_RAD;
		ball_earth.x = BALL_X_INIT;
		ball_earth.y = BALL_Y_INIT;
		ball_earth.x_prev = BALL_X_INIT;
		ball_earth.y_prev = BALL_Y_INIT;
		ball_earth.angle = BALL_ANGLE_INIT;
		ball_earth.step = STEP_INIT;
	}
	ball_redraw(type);
}

// Reinit the ball
void ball_reinit(u8 type)
{
	if(type == TYPE_MARS){
		ball_mars.x_prev = ball_mars.x;
		ball_mars.y_prev = ball_mars.y;
		ball_mars.x = BALL_X_INIT;
		ball_mars.y = BALL_Y_INIT;
		ball_mars.angle = BALL_ANGLE_INIT;
		ball_mars.step = STEP_INIT;
	}
	else{
		ball_earth.x_prev = ball_earth.x;
		ball_earth.y_prev = ball_earth.y;
		ball_earth.x = BALL_X_INIT;
		ball_earth.y = BALL_Y_INIT;
		ball_earth.angle = BALL_ANGLE_INIT;
		ball_earth.step = STEP_INIT;
	}
	ball_redraw(type);
}

// Move the ball of 1 step
void ball_move(u8 type)
{
	if(type == TYPE_MARS){
		// Store previous values of pos
		ball_mars.x_prev = ball_mars.x;
		ball_mars.y_prev = ball_mars.y;
		// Calculate new position
		ball_mars.x -= ball_mars.step*sin(deg2rad(ball_mars.angle));
		ball_mars.y += ball_mars.step*cos(deg2rad(ball_mars.angle));
	}
	else{
		// Store previous values of pos
		ball_earth.x_prev = ball_earth.x;
		ball_earth.y_prev = ball_earth.y;
		// Calculate new position
		ball_earth.x -= ball_earth.step*sin(deg2rad(ball_earth.angle));
		ball_earth.y += ball_earth.step*cos(deg2rad(ball_earth.angle));
	}
}

// Check bounce on palet, updates ball angle if so. Off center bounce changes the angle
bool ball_check_ufo_shock(u8 type)
{
	float ufo_pos_y,y;
	float* angle = NULL;
	float* x = NULL;
	u8 r;
	if(type == TYPE_MARS){
		ufo_pos_y = ufo_pos_y_mars;
		x = &(ball_mars.x);
		y = ball_mars.y;
		r = ball_mars.r;
		angle = &(ball_mars.angle);
	}
	else{
		ufo_pos_y = ufo_pos_y_earth;
		x = &(ball_earth.x);
		y = ball_earth.y;
		r = ball_earth.r;
		angle = &(ball_earth.angle);
	}


	// Check bounce on the bottom
	if (*x > BOTTOM_ROW - r){				// Bottom shock
		float bounce_offset = y - (float)(ufo_pos_y+HALF_UFO_W);
		if (abs(bounce_offset) < HALF_UFO_W+r){		// The ufo is there

			// Update the ball angle
			*angle = (-1.0f)*(*angle) - bounce_offset/(float)(HALF_UFO_W+r)*(float)DELTA_ANGLE_MAX;
			if (normalize(*angle) > ANGLE_MAX)
				*angle = ANGLE_MAX;
			if (normalize(*angle) < ANGLE_MIN)
				*angle = ANGLE_MIN;
			*x += 2*((float)BOTTOM_ROW-(*x+r));
		}

		else{	// Did not catch the ball
			*angle *= -1.0f;
			return false;
		}
	}
	return true;
}

// Check wall bounce, updates angle if so
void ball_check_wall_shock(u8 type)
{
	float* x = NULL;
	float* y = NULL;
	float* angle = NULL;
	u8 r;
	if(type == TYPE_MARS){
		x = &(ball_mars.x);
		y = &(ball_mars.y);
		r = ball_mars.r;
		angle = &(ball_mars.angle);
	}
	else{
		x = &(ball_earth.x);
		y = &(ball_earth.y);
		r = ball_earth.r;
		angle = &(ball_earth.angle);
	}

	// Check wall bounce
	if (*x < r){				// Top shock
		*angle *= -1.0f;
		*x += 2*(r-*x);
	}

	if (*y > SCREEN_WIDTH-r){		// Right shock
		*angle = 180.0f - *angle;
		*y -= 2*(*y-(SCREEN_WIDTH-r));
	}
	else if (*y<r+LEFT_WALL){				// Left shock
		*angle = 180.0f - *angle;
		*y += 2*(r+LEFT_WALL-*y);
	}
}

// Check if ball killed a brick. Update the bombed rows if bomb touched for row killing count
int ball_check_brick_shock(u8 type)
{
	int br_row = -1;
	int br_col = -1;
	bool* bombed_rows;
	player_t* player;
	float step;
	bool shock = false;
	int result = NO_SHOCK;
	float* x = NULL;
	float* y = NULL;
	float* angle = NULL;
	u8 index;
	u8 r;
	if(type == TYPE_MARS){
		bombed_rows = bombed_rows_mars;
		x = &(ball_mars.x);
		y = &(ball_mars.y);
		r = ball_mars.r;
		angle = &(ball_mars.angle);
		step = ball_mars.step;
		index = 0;
		player = &mars_player;
	}
	else{
		bombed_rows = bombed_rows_mars;
		x = &(ball_earth.x);
		y = &(ball_earth.y);
		r = ball_earth.r;
		angle = &(ball_earth.angle);
		step = ball_earth.step;
		index = 1;
		player = &earth_player;
	}

	// Top corner shock
	if (check_point_vs_brick(*x-r , *y , &br_row, &br_col,type)){
		if(brickmap[br_row][br_col][index].type == BTYPE_BOMB){
			int i;
			for(i=0 ; i<MAX_ROWS ; ++i){
				if(brickmap[i][br_col][index].cnt > 0){
					brickmap[i][br_col][index].cnt = 0;
					bombed_rows[i] = true;
				}
				else
					bombed_rows[i] = false;
			}
		}
		else
			brickmap[br_row][br_col][index].cnt--;
		*angle *= -1.0f;
		*x += step/2;
		shock = true;
	}
	// Left corner shock
	else if(check_point_vs_brick(*x , *y-r , &br_row, &br_col,type)){
		if(brickmap[br_row][br_col][index].type == BTYPE_BOMB){
			int i;
			for(i=0 ; i<MAX_ROWS ; ++i){
				if(brickmap[i][br_col][index].cnt > 0){
					brickmap[i][br_col][index].cnt = 0;
					bombed_rows[i] = true;
				}
				else
					bombed_rows[i] = false;
			}
		}
		else
			brickmap[br_row][br_col][index].cnt--;
		*angle = 180.0f - *angle;
		*y += step/2;
		shock = true;
	}
	// Bottom corner shock
	else if (check_point_vs_brick(*x+r , *y , &br_row, &br_col,type)){
		if(brickmap[br_row][br_col][index].type == BTYPE_BOMB){
			int i;
			for(i=0 ; i<MAX_ROWS ; ++i){
				if(brickmap[i][br_col][index].cnt > 0){
					brickmap[i][br_col][index].cnt = 0;
					bombed_rows[i] = true;
				}
				else
					bombed_rows[i] = false;
			}
		}
		else
			brickmap[br_row][br_col][index].cnt--;
		*angle *= -1.0f;
		*x -= step/2;
		shock = true;
	}
	// Right corner shock
	else if(check_point_vs_brick(*x , *y+r , &br_row, &br_col,type)){
		if(brickmap[br_row][br_col][index].type == BTYPE_BOMB){
			int i;
			for(i=0 ; i<MAX_ROWS ; ++i){
				if(brickmap[i][br_col][index].cnt > 0){
					brickmap[i][br_col][index].cnt = 0;
					bombed_rows[i] = true;
				}
				else
					bombed_rows[i] = false;
			}
		}
		else
			brickmap[br_row][br_col][index].cnt--;
		*angle = 180.0f - *angle;
		*y -= step/2;
		shock = true;
	}

	// If shock happened, send row index to know if full row was killed
	if (shock == true){
		player->score += PTS_PER_TOUCH;
		if(brickmap[br_row][br_col][index].type == BTYPE_BOMB)
			result = RESULT_BOMB;
		else
			result = br_row;
	}

	return result;
}

// Returns true if the ball is low enough for the lines to be added
bool ball_check_pos_low(u8 type)
{
	if (type == TYPE_MARS){
		if(ball_mars.x > MAX_X_ROWS){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(ball_earth.x > MAX_X_ROWS){
			return true;
		}
		else{
			return false;
		}
	}
}
