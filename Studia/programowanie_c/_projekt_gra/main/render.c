#include "data.h"
#include "function.c"
void pixel(int color) {
    printf("\033[%dm  \033[0m",color);
}
void pixel_rgb(int rgb) {
    int r = (rgb / 1000000) % 1000;
    int g = (rgb / 1000) % 1000;
    int b = rgb % 1000;
    printf("\033[48;2;%d;%d;%dm  \033[0m", r, g, b);
}
void fill_map_grass(int mapa[MAPAX][MAPAY]){
    for(int x = 0;x < MAPAX;x++){
        for(int y = 0;y < MAPAY;y++){
            mapa[y][x] = B_GRASS;
        }
    }
}
void render(int mapa[MAPAX][MAPAY]){
    //Czyszczenie
    printf("\033[H\033[J");
    for(int x = 0;x < MAPAX;x++){
        for(int i = 0;i < ROZDZIELCZOSC;i++){
            for(int y = 0;y < MAPAY;y++){
                for(int p = 0;p < ROZDZIELCZOSC;p++){
                    RENDER_ENGINE(mapa[y][x]);
                }
            }
            puts("");
        }
        
        
    }
}