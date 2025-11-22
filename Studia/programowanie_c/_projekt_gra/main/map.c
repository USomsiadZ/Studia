#include "data.h"
#include "main.h"
void fill_map_grass(void){
    for(int x = 0;x < MAPAX;x++){
        for(int y = 0;y < MAPAY;y++){
            mapa[y][x][POZIOM_TRAWY] = B_GRASS;
        }
    }
}
//domek
void b_domek(void){
    int hx = 5, hy = 5, hsize = 6;
    for (int x = hx; x < hx + hsize; ++x) {
        for (int y = hy; y < hy + hsize; ++y) {
            if (x == hx || x == hx + hsize - 1 || y == hy || y == hy + hsize - 1) {
                mapa[x][y][0] = B_BOX;
            } else {
                mapa[x][y][0] = B_FLOOR;
            }
        }
    }
    mapa[hx + hsize / 2][hy + hsize - 1][0] = B_GRASS; // wejście

}