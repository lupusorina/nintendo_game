#include <stdint.h>

typedef uint16_t u16;

extern int REG_DISPCNT;
extern int VRAM_A_CR;

extern u16 VRAM_A[10000];

#define MODE_FB0    1
#define VRAM_ENABLE 1
#define VRAM_A_LCD  2

