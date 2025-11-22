#ifndef MAIN_H
#define MAIN_H
#include "data.h"

extern int render_map[MAPAX][MAPAY][MAPAZ];
extern struct characters character[ILOSC_GRACZY];
extern int stary_block;
extern int character_xy[3];
extern struct map map[MAPAX][MAPAY][MAPAZ];

void deklaracja_graczy(void);

#endif