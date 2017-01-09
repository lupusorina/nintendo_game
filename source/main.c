#include <nds.h>
#include <stdio.h>
#include "mars_simulation.h"
#include "background_sub.h"
#include "palet.h"
#include "memory_org.h"
#include "constants.h"

struct sMemoryBases bases = {0, 2, 1, 3};

int main(void) {
    consoleDemoInit();

    mars_start();
    // earth_start();

    //init_background_sub(bases);
    //init_background_main();


    //struct sBuf bg_buf = {BG_TILE_SUB, BG_MAP_SUB, BG_PALETTE_SUB};
    //store_image_background_sub(bg_buf);

    //struct sBuf bg_buf_main = {BG_TILE_MAIN, BG_MAP_MAIN, BG_PALETTE};
    //store_image_background_main(bg_buf_main);


    //struct sBuf obj_buf = {OBJ_GAME_TILE_SUB, OBJ_GAME_MAP_SUB, BG_PALETTE_SUB};
    //place_paddle_initially(obj_buf);

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
    u8 nb_lines_earth = 0;
    u8 dir_earth;
    bool bool_lines_added_earth = false;
    u8 pause = 0;
    while(1){
        scanKeys();
        down = keysDown();
        held = keysHeld();
        dir_mars = NONE;
        dir_earth = NONE;

        if ((down & KEY_L) || (held & KEY_L))
        	dir_mars = LEFT;

        if ((down & KEY_R) || (held & KEY_R))
        	dir_mars = RIGHT;

        if ((down & KEY_LEFT) || (held & KEY_LEFT) || (down & KEY_Y) || (held & KEY_Y))
			dir_earth = LEFT;

		if ((down & KEY_RIGHT) || (held & KEY_RIGHT) || (down & KEY_A) || (held & KEY_A))
			dir_earth = RIGHT;

		if (down & KEY_SELECT){	// Restart game
			pause = (pause+1)%2;
		}

        if (down & KEY_START){	// Restart game
        	mars_restart();
        	//earth_restart();
        	nb_lines_mars = 0;
        	nb_lines_earth = 0;
        }

        // Run sim and communicate the lines between the 2 planets

        if (!pause){
			//printf("lines = %d\n", nb_lines_mars);
			nb_lines_mars += mars_sim_step(dir_mars, nb_lines_mars, &bool_lines_added_mars); // ATTEEENTTTION EARTH ;ARS
			if (bool_lines_added_mars == true){
				bool_lines_added_mars = false;
				nb_lines_mars = 0;
			}
			//nb_lines_mars = earth_sim_step(dir_earth, nb_lines_earth, &bool_lines_added_earth);
			/*if (bool_lines_added_earth == true){
				bool_lines_added_earth = false;
				nb_lines_earth = 0;
			}*/
        }

        swiWaitForVBlank();
    }
    return 0;
}
