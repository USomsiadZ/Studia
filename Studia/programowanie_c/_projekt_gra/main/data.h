#ifndef MAPAX
#define DATA_H

#define ILOSC_GRACZY 1
#define MAPAX 20
#define MAPAY 20
#define MAPAZ 2
#define POZIOM_TRAWY 0
#define B_GRASS 13188121 //42 13188129
#define B_PLAYER 102102102 //100 
#define B_BOX  153116000 //43 
#define B_FLOOR  173136000 //43 
#define ROZDZIELCZOSC 1
#define RENDER_ENGINE pixel_rgb
#include <stdio.h>
struct characters{
    int x;
    int y;
    int z;
    int hand;
    int hp;
};
struct map{
    int x;
    int y;
    int z;
    int id;
    int air;
};
struct item{
    int id;
    int durable;
    int damage;
    int block_attack;
    int placeable;
};
#endif
