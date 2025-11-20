#include "data.h"
#include "render.c"
#include "control.c"

int main(){
    int mapa[MAPAX][MAPAY];
    struct characters character[ILOSC_GRACZY];
    fill_map_grass(mapa);
    for(int i = 0;i < ILOSC_GRACZY;i++){
        character[i].y = 0;
        character[i].x = i;     
    }
    for(int i = 0;i < ILOSC_GRACZY;i++){
        mapa[character[i].x][character[i].y] = 100 + i;
    }
    int character_xy[2] = {character[0].x,character[0].y};
    //int character[3] = {0,0,0};
    
    mapa[2][1] = 50;
    while(1){
        render(mapa);
        printf("\n[x : %d  y: %d]",character_xy[0],character_xy[1]);
        control(character_xy,mapa);
        
    }
    render(mapa);
    return 0;
}