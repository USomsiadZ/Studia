#include "data.h"
#include "render.c"
#include "control.c"
#include "map.c"
#include "multiplayer.c"
#include "main.h"

int mapa[MAPAX][MAPAY][MAPAZ];
struct characters character[ILOSC_GRACZY];
int stary_block = B_GRASS;

int main(){
    fill_map_grass();
    deklaracja_graczy();
    b_domek();
    int character_xy[3] = {character[0].x,character[0].y,character[0].z};
    
    

    while(1){
        render(mapa);
        printf("\n[x : %d  y: %d]",character_xy[0],character_xy[1]);
        printf("[%d]",stary_block);
        stary_block = control(character_xy);
    }
    return 0;
}