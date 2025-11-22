#include "data.h"
#include "main.h"
void fill_map_grass(void){
    for(int x = 0;x < MAPAX;x++){
        for(int y = 0;y < MAPAY;y++){
            render_map[y][x][POZIOM_TRAWY] = B_GRASS;
        }
    }
}
//domek
void b_domek(int hx,int hy,int hsize){
    for (int x = hx; x < hx + hsize; ++x) {
        for (int y = hy; y < hy + hsize; ++y) {
            if (x == hx || x == hx + hsize - 1 || y == hy || y == hy + hsize - 1) {
                render_map[x][y][0] = B_BOX;
            } else {
                render_map[x][y][0] = B_FLOOR;
            }
        }
    }
    render_map[hx + hsize / 2][hy + hsize - 1][0] = B_GRASS; // wejście

}