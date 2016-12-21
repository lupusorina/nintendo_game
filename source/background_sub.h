#ifndef BACKGROUND_SUB_H_
#define BACKGROUND_SUB_H_

#include <nds.h>
#include <stdio.h>
#include "../data/cosmos2.h"
#include "memory_org.h"

void init_background_sub(struct sMemoryBases base);
void store_image_background_sub(struct sBuf bf);

#endif