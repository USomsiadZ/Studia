#include "data.h"
int control(int character[3], int mapa[MAPAX][MAPAY][MAPAZ],int stary_block) {
    char znak;
    if (scanf(" %c", &znak) != 1) {
        return stary_block;
    }

    int x = character[0];
    int y = character[1];
    int z = character[2];
    mapa[x][y][z] = stary_block;
    switch (znak) {
        case 'a':
            if (x > 0 && (mapa[x-1][y][z] ==B_GRASS || mapa[x][y + 1][z] == B_FLOOR)) {
                x -= 1;
            }
            break;
        case 'd':
            if (x + 1 < MAPAX && (mapa[x+1][y][z]==B_GRASS || mapa[x][y + 1][z] == B_FLOOR)) {
                x += 1;
            }
            break;
        case 'w':
            if (y > 0 && (mapa[x][y - 1][z]==B_GRASS || mapa[x][y + 1][z] == B_FLOOR)) {
                y -= 1;
            }
            break;
        case 's':
            if (y + 1 < MAPAY && (mapa[x][y + 1][z]==B_GRASS || mapa[x][y + 1][z] == B_FLOOR)) {
                y += 1;
            }
            break;
        default:
            return stary_block;
    }


    stary_block = mapa[x][y][z];
    //mapa[character[0]][character[1]][character[2]] = stary_block;
    character[0] = x;
    character[1] = y;
    character[2] = z;
    mapa[x][y][z] = B_PLAYER;
    return stary_block;
}