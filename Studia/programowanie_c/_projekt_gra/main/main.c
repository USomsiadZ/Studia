#include "data.h"
#include "render.c"
#include "control.c"
#include "map.c"
#include "multiplayer.c"
#include "main.h"

int render_map[MAPAX][MAPAY][MAPAZ];
struct characters character[ILOSC_GRACZY];
int stary_block = B_GRASS;
struct map map[MAPAX][MAPAY][MAPAZ];

int main(){
    fill_map_grass();
    deklaracja_graczy();
    b_domek(2,5,6);

    while(1){
        render(render_map);
        printf("\n[x : %d  y: %d]",character[0].x,character[0].y);
        printf("[%d]",stary_block);
        stary_block = control();
    }
    return 0;
}