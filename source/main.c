/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "background_sub.h"
#include "palet.h"

int main(void) {

    consoleDemoInit();

    init_background_sub();
    store_image_background_sub();
    place_palet();
    while(1)
        swiWaitForVBlank();	
}
