#include <nds.h>
#include <stdio.h>
#include "background_sub.h"
#include "palet.h"
#include "memory_org.h"

struct sMemoryBases bases = {0, 2, 1, 3};



int main(void) {

    consoleDemoInit();
    init_background_sub(bases);

    struct sBuf bg_buf = {BG_TILE_SUB, BG_MAP_SUB, BG_PALETTE_SUB};
    store_image_background_sub(bg_buf);

    struct sBuf obj_buf = {OBJ_GAME_TILE_SUB, OBJ_GAME_MAP_SUB, BG_PALETTE_SUB};
    place_paddle_initially(obj_buf);


    scanKeys();
    irqInit();
    REG_KEYCNT = (1 << 14) | KEY_A | KEY_B | KEY_START;
    irqSet(IRQ_KEYS, &move_palet);

    irqEnable(IRQ_KEYS);
    irqEnable(IRQ_VBLANK);

    while(1){
        scanKeys();
        swiWaitForVBlank();
    }
    return 0;
}
