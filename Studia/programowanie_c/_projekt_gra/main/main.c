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

    while(1){
        render(mapa);
        printf("\n[x : %d  y: %d]",character[0].x,character[0].y);
        printf("[%d]",stary_block);
        stary_block = control();
    }
    return 0;
}