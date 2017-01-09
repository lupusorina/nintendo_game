/*
 * brickmap.c
 *
 *  Created on: Jan 9, 2017
 *      Author: tardyantoine
 *      Handles the brickmap
 */

#include <nds.h>
#include "brickmap.h"
#include <stdio.h>

// Check if a full row has been killed, in order to add lines to the opponent
u16 brickmap_check_killed_row(u8 row)
{
	int i;
	for(i=0 ; i<NB_COLS ; ++i){
		if(brickmap[row][i].cnt > 0){
			return 0;
		}
	}
	return 1;
}

// Init the brickmap array and draws the initial brickmap
void brickmap_init()
{
	int i,j;
	for(i=0 ; i<MAX_ROWS ; ++i){
		for(j=0 ; j<NB_COLS ; ++j){
			brickmap[i][j].type = BTYPE_STD;
			if (i<NB_ROWS_INIT)
				brickmap[i][j].cnt = 1;
			else
				brickmap[i][j].cnt = 0;
		}
	}
	brickmap_redraw();
}

// Draws a brick at position row, col
void draw_brick(int row, int col)
{
	int top = MARGIN + row*BRICK_H;
	int bottom = top + BRICK_H;
	int left = MARGIN + col*BRICK_W;
	int right = left + BRICK_W;
	int cnt = brickmap[row][col].cnt;
	int i,j;

	for(i = top; i < bottom; i++){
		for(j = left; j < right; j++){
			if(cnt<1)
				BG_GFX[i*SCREEN_WIDTH + j] = BLACK_COLOR;	// Transparent
			else{
				if(i==top || i==bottom-1 || j==left || j==right-1)
					BG_GFX[i*SCREEN_WIDTH + j] = BORDER_COLOR;	// Rectangle around brick
				else{
					// Fill the brick depending on counter
					switch(cnt){
					case 3:
						BG_GFX[i*SCREEN_WIDTH + j] = BRICK_COLOR_3;
						break;
					case 2:
						BG_GFX[i*SCREEN_WIDTH + j] = BRICK_COLOR_2;
						break;
					case 1:
						BG_GFX[i*SCREEN_WIDTH + j] = BRICK_COLOR_1;
						break;
					case 0:
					default:
						BG_GFX[i*SCREEN_WIDTH + j] = BLACK_COLOR;
						break;
					};
				}
			}
		}
	}
}

// Redraws the whole brickmap
void brickmap_redraw()
{
	int i,j;
	for(i=0 ; i<MAX_ROWS ; ++i){
		for(j=0 ; j<NB_COLS ; ++j){
			draw_brick(i,j);
		}
	}
}

// Add a row on top of a player, takes all others down
int brickmap_add_rows(u8 nb)
{
	// Check if last row is empty
	int col;
	int row;
	for(row=MAX_ROWS-1 ; row>MAX_ROWS-1-nb ; --row){
		for(col=0 ; col<NB_COLS ; ++col){
			if(brickmap[row][col].cnt>0)
				return LOST;
		}
	}

	// Shift all rows down
	for(row=MAX_ROWS-1 ; row>nb-1 ; --row){
		for(col=0 ; col<NB_COLS ; ++col){
			brickmap[row][col].type = brickmap[row-nb][col].type;
			brickmap[row][col].cnt = brickmap[row-nb][col].cnt;
		}
	}

	// Fill nb first lines with bricks
	for(row=0 ; row<nb ; ++row){
		for(col=0 ; col<NB_COLS ; ++col){
			brickmap[row][col].type = BTYPE_STD;
			brickmap[row][col].cnt = 1;
		}
	}

	return NOT_LOST;
}
