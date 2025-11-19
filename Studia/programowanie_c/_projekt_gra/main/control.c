#include "data.h"
void control(int character[2], int mapa[MAPAX][MAPAY]) {
    char znak;
    if (scanf(" %c", &znak) != 1) {
        return;
    }

    int x = character[0];
    int y = character[1];

    switch (znak) {
        case 'w':
            if (x > 0) {
                x -= 1;
            }
            break;
        case 's':
            if (x + 1 < MAPAX) {
                x += 1;
            }
            break;
        case 'a':
            if (y > 0) {
                y -= 1;
            }
            break;
        case 'd':
            if (y + 1 < MAPAY) {
                y += 1;
            }
            break;
        default:
            return;
    }

    if (x == character[0] && y == character[1]) {
        return;
    }

    mapa[character[0]][character[1]] = 42;
    character[0] = x;
    character[1] = y;
    mapa[x][y] = 100;
}