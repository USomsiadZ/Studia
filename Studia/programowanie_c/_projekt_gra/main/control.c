#include "data.h"
void control(int character[2], int mapa[MAPAX][MAPAY]) {
    char znak;
    if (scanf(" %c", &znak) != 1) {
        return;
    }

    int x = character[0];
    int y = character[1];

    switch (znak) {
        case 'a':
            if (x > 0 && mapa[x-1][y]==B_GRASS ) {
                x -= 1;
            }
            break;
        case 'd':
            if (x + 1 < MAPAX && mapa[x+1][y]==B_GRASS) {
                x += 1;
            }
            break;
        case 'w':
            if (y > 0 && mapa[x][y - 1]==B_GRASS) {
                y -= 1;
            }
            break;
        case 's':
            if (y + 1 < MAPAY && mapa[x][y + 1]==B_GRASS) {
                y += 1;
            }
            break;
        default:
            return;
    }

    if (x == character[0] && y == character[1]) {
        return;
    }

    mapa[character[0]][character[1]] = B_GRASS;
    character[0] = x;
    character[1] = y;
    mapa[x][y] = B_PLAYER;
}