#ifndef MAIN_H
#define MAIN_H
#include "data.h"

extern int mapa[MAPAX][MAPAY][MAPAZ];
extern struct characters character[ILOSC_GRACZY];
extern int stary_block;

void deklaracja_graczy(void);

#endif