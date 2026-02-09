#include "main.h"
void deklaracja_graczy(void){
    for(int i = 0;i < ILOSC_GRACZY;i++){
        character[i].y = 0;
        character[i].x = i;     
        character[i].z = 0;     
    }
    for(int i = 0;i < ILOSC_GRACZY;i++){
        render_map[character[i].x][character[i].y][character[i].z] = B_PLAYER;
    }
}