/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "background_sub.h"

int main(void) {
	
    consoleDemoInit();

    init_background_sub();
    store_image_background_sub();

    while(1)
        swiWaitForVBlank();	
}
