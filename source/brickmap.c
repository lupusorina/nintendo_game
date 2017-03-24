/*
 * brickmap.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the brickmap
 */

#include <nds.h>
#include "brickmap.h"

// ===== GLOBAL VARS ===========================================================
u8 acc_mars_bombs;		// Accs to know when to add a bomb
u8 acc_earth_bombs;		// Accs to know when to add a bomb

// ===== BRICKMAP FUNC IMPLEMENTATIONS =========================================
// Util min val
int min(int a, int b)
{
	if(a <= b)
		return a;
	else
		return b;
}

// Check if a row was killed by a bomb, returns the number of killed rows
u16 brickmap_check_killed_row_bomb(u8 type)
{
	int i,j;
	u8 ret = 0;
	bool killed = true;
	bool* bombed_rows;
	if(type == TYPE_MARS)
		bombed_rows = bombed_rows_mars;
	else
		bombed_rows = bombed_rows_mars;

	// Use the bombed_rows array to know whick bricks existed before
	for(i=0 ; i<MAX_ROWS ; ++i){
		killed = true;
		if(bombed_rows[i] == true){
			for(j=0 ; j<NB_COLS ; ++j){
				if(brickmap[i][j][type].cnt > 0){
					killed = false;
				}
			}
			if(killed == true)
				ret++;
		}
	}
	return ret;
}

// Check if a full row has been killed, in order to add lines to the opponent, must know whick row was touched
u16 brickmap_check_killed_row(u8 row, u8 type)
{
	int i;
	for(i=0 ; i<NB_COLS ; ++i){
		if(brickmap[row][i][type].cnt > 0){
			return 0;
		}
	}
	return 1;
}

// Init the brickmap array and draws the initial brickmap
void brickmap_init(u8 type)
{
	acc_mars_bombs = 0;
	acc_earth_bombs = 0;
	bomb_color = BOMB_COLOR_1;
	int i,j;
	for(i=0 ; i<MAX_ROWS ; ++i){
		for(j=0 ; j<NB_COLS ; ++j){
			brickmap[i][j][type].type = BTYPE_STD;
			if (i<NB_ROWS_INIT)
				brickmap[i][j][type].cnt = 1;
			else
				brickmap[i][j][type].cnt = 0;
		}
	}
	brickmap_redraw(type);
}

// Draws a brick at position row, col in type screen
void draw_brick(int row, int col, u8 type)
{
	// Checks where to draw
	int top,bottom,left,right;
	if(!AI && type == TYPE_MARS){
		bottom = SCREEN_HEIGHT - 1 - MARGIN - row*BRICK_H;
		top = bottom - BRICK_H;
		right = SCREEN_WIDTH - 1 - LEFT_WALL - MARGIN - col*BRICK_W;
		left = right - BRICK_W;
	}
	else{
		top = MARGIN + row*BRICK_H;
		bottom = top + BRICK_H;
		left = MARGIN + LEFT_WALL + col*BRICK_W;
		right = left + BRICK_W;
	}
	int cnt = brickmap[row][col][type].cnt;
	int brick_type = brickmap[row][col][type].type;
	int i,j;
	u16 bg_color;
	u16* gfx_buffer = NULL;
	if(type == TYPE_MARS){
		gfx_buffer = GFX_MARS;
		bg_color = MARS_BG_COLOR;
	}
	else{
		gfx_buffer = GFX_EARTH;
		bg_color = EARTH_BG_COLOR;
	}

	// Draw with correct color
	for(i = top; i < bottom; i++){
		for(j = left; j < right; j++){
			if(cnt<1)
				gfx_buffer[i*SCREEN_WIDTH + j] = bg_color;	// Transparent
			else{
				if(i==top || i==bottom-1 || j==left || j==right-1)
					gfx_buffer[i*SCREEN_WIDTH + j] = BORDER_COLOR;	// Rectangle around brick
				else{
					if(brick_type == BTYPE_BOMB){
						gfx_buffer[i*SCREEN_WIDTH + j] = bomb_color;
					}
					else{
						// Fill the brick depending on counter
						switch(cnt){
						case 5:
							gfx_buffer[i*SCREEN_WIDTH + j] = BRICK_COLOR_5;
							break;
						case 4:
							gfx_buffer[i*SCREEN_WIDTH + j] = BRICK_COLOR_4;
							break;
						case 3:
							gfx_buffer[i*SCREEN_WIDTH + j] = BRICK_COLOR_3;
							break;
						case 2:
							gfx_buffer[i*SCREEN_WIDTH + j] = BRICK_COLOR_2;
							break;
						case 1:
							gfx_buffer[i*SCREEN_WIDTH + j] = BRICK_COLOR_1;
							break;
						case 0:
						default:
							gfx_buffer[i*SCREEN_WIDTH + j] = BRICK_COLOR_5; // Higher than 3
							break;
						};
					}
				}
			}
		}
	}
}

// Redraws the whole brickmap
void brickmap_redraw(u8 type)
{
	int i,j;
	for(i=0 ; i<MAX_ROWS ; ++i){
		for(j=0 ; j<NB_COLS ; ++j){
			draw_brick(i,j,type);
		}
	}
}

// Redraws only the bombs, for the blinking
void brickmap_redraw_bombs(u8 type){
	int i,j;
	for(i=0 ; i<MAX_ROWS ; ++i){
		for(j=0 ; j<NB_COLS ; ++j){
			if(brickmap[i][j][type].type == BTYPE_BOMB)
				draw_brick(i,j,type);
		}
	}
}

// Add nb rows on top of a player, takes all others down, return if player has lost
int brickmap_add_rows(u8 nb, u8 type)
{
	// Check if last row is empty
	int col;
	int row;
	int inc;
	u8* acc;
	if(type == TYPE_MARS){
		acc = &acc_mars_bombs;
		inc = min((int)((earth_player.level+1)/2),MAX_CNT);
	}
	else
	{
		acc = &acc_earth_bombs;
		inc = min((int)((mars_player.level+1)/2),MAX_CNT);
	}
	for(row=MAX_ROWS-1 ; row>MAX_ROWS-1-nb ; --row){
		for(col=0 ; col<NB_COLS ; ++col){
			if(brickmap[row][col][type].cnt>0)
				return LOST;
		}
	}

	// Shift all rows down
	for(row=MAX_ROWS-1 ; row>nb-1 ; --row){
		for(col=0 ; col<NB_COLS ; ++col){
			brickmap[row][col][type].type = brickmap[row-nb][col][type].type;
			brickmap[row][col][type].cnt = brickmap[row-nb][col][type].cnt;
		}
	}

	// Fill nb first lines with bricks
	for(row=0 ; row<nb ; ++row){
		for(col=0 ; col<NB_COLS ; ++col){
			*acc += 1;
			if(*acc < NB_BRICKS_BEFORE_BOMB){
				brickmap[row][col][type].type = BTYPE_STD;
				brickmap[row][col][type].cnt = inc;
			}
			else{
				*acc = 0;
				brickmap[row][col][type].type = BTYPE_BOMB;
				brickmap[row][col][type].cnt = 1;
			}
		}
	}

	return NOT_LOST;
}
