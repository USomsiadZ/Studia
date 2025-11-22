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

void render(int render_map[MAPAX][MAPAY][MAPAZ]){
    //Czyszczenie
    printf("\033[H\033[J");
    //todo 1 -> render_map z
    for(int z = 0;z < 1;z++){
        for(int x = 0;x < MAPAX;x++){
            for(int i = 0;i < ROZDZIELCZOSC;i++){
                for(int y = 0;y < MAPAY;y++){
                    for(int p = 0;p < ROZDZIELCZOSC;p++){
                        RENDER_ENGINE(render_map[y][x][z]);
                    }
                }
                puts("");
            }
        }
    }
}
void map_to_render(int render_map[MAPAX][MAPAY][MAPAZ],int map[MAPAX][MAPAY][MAPAZ]){
    for(int z = 0;z < 1;z++){
        for(int x = 0;x < MAPAX;x++){
            for(int i = 0;i < ROZDZIELCZOSC;i++){
                for(int y = 0;y < MAPAY;y++){
                    render_map[x][y][z] = map[x][y][z];
                }
                puts("");
            }
        }
    }
}
