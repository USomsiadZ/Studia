#include "data.h"
void fill_map_grass(int mapa[MAPAX][MAPAY][MAPAZ]){
    for(int x = 0;x < MAPAX;x++){
        for(int y = 0;y < MAPAY;y++){
            mapa[y][x][POZIOM_TRAWY] = B_GRASS;
        }
    }
}