#include "data.h"
#include "render.c"
#include "control.c"
#include "map.c"

int main(){
    int mapa[MAPAX][MAPAY][MAPAZ];
    struct characters character[ILOSC_GRACZY];
    int stary_block = B_GRASS;
    fill_map_grass(mapa);
    for(int i = 0;i < ILOSC_GRACZY;i++){
        character[i].y = 0;
        character[i].x = i;     
        character[i].z = 0;     
    }
    for(int i = 0;i < ILOSC_GRACZY;i++){
        mapa[character[i].x][character[i].y][character[i].z] = B_PLAYER;
    }
    int character_xy[3] = {character[0].x,character[0].y,character[0].z};
    //int character[3] = {0,0,0};
    
    // ...existing code...
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
// ...existing code...
    while(1){
        render(mapa);
        printf("\n[x : %d  y: %d]",character_xy[0],character_xy[1]);
        printf("[%d]",stary_block);
        stary_block = control(character_xy,mapa,stary_block);
    }
    render(mapa);
    return 0;
}