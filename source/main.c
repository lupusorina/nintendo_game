#include <nds.h>
#include "mars_simulation.h"
#include "earth_simulation.h"
#include "start_pic.h"
#include "constants.h"

//struct sMemoryBases bases = {0, 2, 1, 3};

// GLOBAL
brick_t brickmap[MAX_ROWS][NB_COLS][2];		// Maps of the bricks
bool AI = false;
player_t mars_player;
player_t earth_player;
u16 bomb_color;

// ISR timer, blink bombs at 1 Hz
void ISR_TIMER1()
{
	if(bomb_color == BOMB_COLOR_1)
		bomb_color = BOMB_COLOR_2;
	else
		bomb_color = BOMB_COLOR_1;

	redraw();
}

void display_start()
{
		VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
		REG_DISPCNT_SUB = MODE_5_2D  | DISPLAY_BG2_ACTIVE;
	    // Initialize Background
		BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256 ;//| BG_PRIORITY_0 | BG_WRAP_ON;

	    // Affine Marix Transformation
	    REG_BG2PA_SUB = 256;
	    REG_BG2PC_SUB = 0;
	    REG_BG2PB_SUB = 0;
	    REG_BG2PD_SUB = 256;

	    swiCopy(start_picBitmap, BG_BMP_RAM_SUB(0), start_picBitmapLen/2);
		swiCopy(start_picPal, BG_PALETTE_SUB, start_picPalLen/2);;
}

int main(void) {



    TIMER_DATA(1) = (TIMER_FREQ_1024(2));
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER1, &ISR_TIMER1);
	irqEnable(IRQ_TIMER1);


    mars_start();
    earth_start();
    display_start();

    scanKeys();
    /*irqInit();
    REG_KEYCNT = (1 << 14) | KEY_A | KEY_B | KEY_START | KEY_L | KEY_R;
    irqSet(IRQ_KEYS, &move_palet);

    irqEnable(IRQ_KEYS);*/
    irqEnable(IRQ_VBLANK);

    u16 down;
    u16 held;

    u8 nb_lines_mars = 0;
    u8 dir_mars;
    bool bool_lines_added_mars = false;
    bool bool_mars_lost = false;

    u8 nb_lines_earth = 0;
    u8 dir_earth;
    bool bool_lines_added_earth = false;
    bool bool_earth_lost = false;

    u8 pause = 1;
    u8 reset = 1;
    while(1){
        scanKeys();
        down = keysDown();
        held = keysHeld();
        dir_mars = NONE;
        dir_earth = NONE;

        if(AI)
        	dir_mars = mars_ai_plays();
        else{
			if ((down & KEY_L) || (held & KEY_L))
				dir_mars = RIGHT;

			if ((down & KEY_R) || (held & KEY_R))
				dir_mars = LEFT;
        }

        if(down & KEY_TOUCH && reset == 1){
        	mars_restart();
        	earth_restart();
        	pause = 1;
        	reset = 0;
        }

        if (down & KEY_X){
        	if(AI)
        		AI = false;
        	else
        		AI = true;

        	mars_restart();
			earth_restart();
			display_start();
			reset = 1;
			TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
			nb_lines_mars = 0;
			bool_lines_added_mars = false;
			bool_mars_lost = false;

			nb_lines_earth = 0;
			bool_lines_added_earth = false;
			bool_earth_lost = false;
			pause = 1;
        }

        if ((down & KEY_LEFT) || (held & KEY_LEFT) || (down & KEY_Y) || (held & KEY_Y))
			dir_earth = RIGHT;

		if ((down & KEY_RIGHT) || (held & KEY_RIGHT) || (down & KEY_A) || (held & KEY_A))
			dir_earth = LEFT;

		if (down & KEY_START && reset == 0){	// Pause game
			pause = (pause+1)%2;
		}

		if (down & KEY_LID){	// Pause game
			pause = 1;
		}

        if (down & KEY_SELECT){	// Restart game
        	reset = 1;
        	mars_restart();
        	earth_restart();
        	display_start();
        	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
        	nb_lines_mars = 0;
			bool_lines_added_mars = false;
			bool_mars_lost = false;

			nb_lines_earth = 0;
			bool_lines_added_earth = false;
			bool_earth_lost = false;
			pause = 1;
        }

        // Run sim and communicate the lines between the 2 planets

        if (!pause && !bool_mars_lost && !bool_earth_lost){
			nb_lines_earth += mars_sim_step(dir_mars, nb_lines_mars, &bool_lines_added_mars, &bool_mars_lost); // ATTEEENTTTION EARTH ;ARS
			if (bool_lines_added_mars == true){
				bool_lines_added_mars = false;
				nb_lines_mars = 0;
			}

			nb_lines_mars += earth_sim_step(dir_earth, nb_lines_earth, &bool_lines_added_earth, &bool_earth_lost);
			if (bool_lines_added_earth == true){
				bool_lines_added_earth = false;
				nb_lines_earth = 0;
			}
        }

        if (bool_mars_lost){
			mars_loses();
			earth_wins();
			TIMER1_CR = (0<<7) | TIMER_DIV_1024 | TIMER_IRQ_REQ;
		}
        else if (bool_earth_lost){
			mars_wins();
			earth_loses();
			TIMER1_CR = (0<<7) | TIMER_DIV_1024 | TIMER_IRQ_REQ;
		}

        swiWaitForVBlank();
    }
    return 0;
}
