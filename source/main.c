/*
 * main.c
 *
 *  Created on: Jan 6, 2017
 *      Author: tardyantoine (+ Weathley)
 *
 *      Core of the project, handling the high level sim and keys and timers
 */

#include <nds.h>
#include "mars_simulation.h"
#include "earth_simulation.h"
#include "start_pic.h"
#include "start_pic_1v1.h"
#include "start_top.h"
#include "constants.h"
#include "audio.h"

// ===== GLOBAL VARS ===========================================================
brick_t brickmap[MAX_ROWS][NB_COLS][2];			// Maps of the bricks (2 levels)
bool AI = true;									// true: mode vs AI, false: mode vs player
player_t mars_player;							// Struct representing the mars (top) player
player_t earth_player;							// Struct representing the earth (sub) player
u16 bomb_color;									// Color of the bomb bricks, updated by the timer
u16 timer_mode;									// Bomb for 4Hz blink, Lost for 3 sec before restart
u16	restart_acc;								// Accumulator for restart

// ===== UTILS =================================================================
// ISR timer, blink vertical bombs at 2 Hz
void ISR_TIMER1()
{
	if(timer_mode == TIMER_BOMB){
		// Toggle color
		if(bomb_color == BOMB_COLOR_1)
			bomb_color = BOMB_COLOR_2;
		else
			bomb_color = BOMB_COLOR_1;

		// Redraw event, for sync, if not in reset mode
		redraw();
		restart_acc = 0;
	}
	else if(timer_mode == TIMER_LOST){
		restart_acc++;
	}
	else if(timer_mode == TIMER_OFF){
		;
	}
}

// Display the correct start menus (instructions). Call at reset
void display_start()
{
	// Switch backgrounds to palettes
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256 ;	// Main
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256; //Sub

	// Print instructions on top screen
	swiCopy(start_topBitmap, BG_BMP_RAM(0), start_topBitmapLen/2);
	swiCopy(start_topPal, BG_PALETTE, start_topPalLen/2);

	// Print start menu on SUB screen
	if(AI){ // AI mode
		swiCopy(start_picBitmap, BG_BMP_RAM_SUB(0), start_picBitmapLen/2);
		swiCopy(start_picPal, BG_PALETTE_SUB, start_picPalLen/2);
	}
	else{ // PvP mode
		swiCopy(start_pic_1v1Bitmap, BG_BMP_RAM_SUB(0), start_pic_1v1BitmapLen/2);
		swiCopy(start_pic_1v1Pal, BG_PALETTE_SUB, start_pic_1v1PalLen/2);
	}
}

// ===== MAIN CORE =============================================================
int main(void) {

	// Handle music
	audio_init();

	// Setup timer at 4 Hz for the blinking bombs
    TIMER_DATA(1) = (TIMER_FREQ_1024(4));
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER1, &ISR_TIMER1);
	irqEnable(IRQ_TIMER1);
	timer_mode = TIMER_BOMB;

	// Init the game and go to reset screen
    mars_start();
    earth_start();
    display_start();

    // Handle the scanning problem (non empty at boot)
    scanKeys();
    irqEnable(IRQ_VBLANK);

    // === High level sim variables ===
    u16 down;								// Stores pressed keys
    u16 held;								// Stores held keys
    u8 nb_lines_mars = 0;					// Sends lines to be added to Earth
    u8 dir_mars;							// Sends direction played by Mars
    bool bool_lines_added_mars = false;		// True when the lines to be added to Mars actually are
    bool bool_mars_lost = false;			// Set to true if Mars lost
    u8 nb_lines_earth = 0;					// Sends lines to be added to Mars
    u8 dir_earth;							// Sends direction played by Earth
    bool bool_lines_added_earth = false;	// True when the lines to be added to Earth actually are
    bool bool_earth_lost = false;			// Set tu true if Earth lost
    u8 pause = 1;							// 1 = game paused, 0 = game running
    u8 reset = 1;							// 1 = reset screen, o = game on!!!
    touchPosition touch;					// Stores the touch position

    // ===== FINITE STATE MACHINE, GlaDOS MAIN CORE ============================
    while(1){

    	// Scan keys
        scanKeys();
        down = keysDown();
        held = keysHeld();

        dir_mars = NONE;
        dir_earth = NONE;

        // === KEYS HANDLER ====================================================
        // Handle touches if game running, sends directions to Earth
        touchRead(&touch);
        // Note: Send direction and not position, otherwise big advantage for touchscreen player
    	if(touch.px){
    		if(touch.px < 128)
    			dir_earth = RIGHT;
    		else
    			dir_earth = LEFT;
    	}

    	// Sends directions to Mars, either by player or by AI
        if(AI)
        	dir_mars = mars_ai_plays();
        else{
			if ((down & KEY_L) || (held & KEY_L))
				dir_mars = LEFT;

			if ((down & KEY_R) || (held & KEY_R))
				dir_mars = RIGHT;
        }

        // In reset screen, touch to start game (in paused mode)
        if(down & KEY_TOUCH && reset == 1){
        	// If switch mode is touched, switch mode
        	if(touch.px > 12 && touch.px < 244 && touch.py > 99 && touch.py < 144){
        		// Toggle AI
				if(AI)
					AI = false;
				else
					AI = true;

				// Change screen display mode
				display_start();
        	}
        	else{ // Else start game
				mars_restart();
				earth_restart();
				audio_start_music();
				pause = 1;
				reset = 0;
        	}
        }

        // Switch playing mode (toggle AI or PvP)
        if (down & KEY_X){
        	// Toggle AI
        	if(AI)
        		AI = false;
        	else
        		AI = true;

        	audio_stop_music();
        	// Reset game, goto reset screen and stops blink
			display_start();
			reset = 1;
			timer_mode = TIMER_OFF;
			nb_lines_mars = 0;
			bool_lines_added_mars = false;
			bool_mars_lost = false;
			nb_lines_earth = 0;
			bool_lines_added_earth = false;
			bool_earth_lost = false;
			pause = 1;
        }

        // Send directions to Earth
        if ((down & KEY_LEFT) || (held & KEY_LEFT) || (down & KEY_Y) || (held & KEY_Y))
			dir_earth = RIGHT;
		if ((down & KEY_RIGHT) || (held & KEY_RIGHT) || (down & KEY_A) || (held & KEY_A))
			dir_earth = LEFT;

		// START = Toggle pause if not in reset screen
		if (down & KEY_START){
			if (reset == 0){
				pause = (pause+1)%2;
				if (pause == 1){
					audio_pause_music();
					timer_mode = TIMER_OFF;
				}
				else{
					audio_restart_music();
					timer_mode = TIMER_BOMB;
				}
			}
			else if(reset == 1){
				mars_restart();
				earth_restart();
				audio_start_music();
				pause = 1;
				reset = 0;
			}
		}

		// LID = Pause game if lid is closed
		if (down & KEY_LID){
			pause = 1;
			audio_pause_music();
		}

		// SELECT = Reset game and go to reset screen
        if (down & KEY_SELECT){
        	audio_stop_music();
        	reset = 1;
        	display_start();
        	timer_mode = TIMER_OFF;
        	nb_lines_mars = 0;
			bool_lines_added_mars = false;
			bool_mars_lost = false;
			nb_lines_earth = 0;
			bool_lines_added_earth = false;
			bool_earth_lost = false;
			pause = 1;
        }

        // === SIMULATION STEP =================================================
        // Run sim and communicate between the 2 planets via portals
        if (!pause && !bool_mars_lost && !bool_earth_lost){

        	// Run Mars step and stores lines to be added to Earth (one per killed row in Mars)
			nb_lines_earth += mars_sim_step(dir_mars, nb_lines_mars, &bool_lines_added_mars, &bool_mars_lost); // ATTEEENTTTION EARTH ;ARS

			// Lines can only be added if ball is off the brickmap, checking here
			if (bool_lines_added_mars == true){
				bool_lines_added_mars = false;
				nb_lines_mars = 0;
			}

			// Run Earth step and stores lines to be added to Mars (one per killed row in Earth)
			nb_lines_mars += earth_sim_step(dir_earth, nb_lines_earth, &bool_lines_added_earth, &bool_earth_lost);

			// Lines can only be added if ball is off the brickmap, checking here
			if (bool_lines_added_earth == true){
				bool_lines_added_earth = false;
				nb_lines_earth = 0;
			}
        }

        // Handles losing situations
        if (bool_mars_lost){
			mars_loses();
			earth_wins();
			timer_mode = TIMER_LOST;
			audio_stop_music();
			if(restart_acc > TICKS_BEFORE_RESTART || down & KEY_START){
				restart_acc = 0;
				reset = 1;
				display_start();
				timer_mode = TIMER_OFF;
				nb_lines_mars = 0;
				bool_lines_added_mars = false;
				bool_mars_lost = false;
				nb_lines_earth = 0;
				bool_lines_added_earth = false;
				bool_earth_lost = false;
				pause = 1;
			}
		}
        else if (bool_earth_lost){
			mars_wins();
			earth_loses();
			timer_mode = TIMER_LOST;
			audio_stop_music();
			if(restart_acc > TICKS_BEFORE_RESTART || down & KEY_START){
				restart_acc = 0;
				reset = 1;
				display_start();
				timer_mode = TIMER_OFF;
				nb_lines_mars = 0;
				bool_lines_added_mars = false;
				bool_mars_lost = false;
				nb_lines_earth = 0;
				bool_lines_added_earth = false;
				bool_earth_lost = false;
				pause = 1;
			}
		}
        swiWaitForVBlank();
    }
    return 0;
}

// The cake is a lie...

