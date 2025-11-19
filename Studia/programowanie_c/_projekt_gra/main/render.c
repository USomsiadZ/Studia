#include "data.h"
void pixel(int color) {
    printf("\033[%dm  \033[0m",color);
}
void fill_map_grass(int mapa[MAPAX][MAPAY]){
    for(int x = 0;x < MAPAX;x++){
        for(int y = 0;y < MAPAY;y++){
            mapa[x][y] = 42;
        }
    }
}
void render(int mapa[MAPAX][MAPAY]){
    //Czyszczenie
    printf("\033[H\033[J");
    for(int x = 0;x < MAPAX;x++){
        for(int y = 0;y < MAPAY;y++){
            //printf("%d",mapa[x][y]);
            pixel(mapa[x][y]);
        }
        puts("");
    }
}