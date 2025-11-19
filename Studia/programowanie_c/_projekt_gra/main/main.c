#include "data.h"
#include "render.c"
#include "control.c"

int main() {
    int mapa[MAPAX][MAPAY];
    int character[3] = {0,0,0};
    fill_map_grass(mapa);
    mapa[character[0]][character[1]] = 100;
    mapa[0][1] = 43;
    while(1){
        render(mapa);
        control(character,mapa);
    }
    render(mapa);
    return 0;
}