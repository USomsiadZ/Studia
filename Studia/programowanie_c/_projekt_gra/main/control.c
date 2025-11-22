#include "data.h"
#include "main.h"
int control() {
    char znak;
    if (scanf(" %c", &znak) != 1) {
        return stary_block;
    }
    int x = character[0].x;
    int y = character[0].y;
    int z = character[0].z;
    render_map[x][y][z] = stary_block;
    switch (znak) {
        case 'a':
            if (x > 0 && (render_map[x-1][y][z] ==B_GRASS || render_map[x][y + 1][z] == B_FLOOR)) {
                x -= 1;
            }
            break;
        case 'd':
            if (x + 1 < MAPAX && (render_map[x+1][y][z]==B_GRASS || render_map[x][y + 1][z] == B_FLOOR)) {
                x += 1;
            }
            break;
        case 'w':
            if (y > 0 && (render_map[x][y - 1][z]==B_GRASS || render_map[x][y + 1][z] == B_FLOOR)) {
                y -= 1;
            }
            break;
        case 's':
            if (y + 1 < MAPAY && (render_map[x][y + 1][z]==B_GRASS || render_map[x][y + 1][z] == B_FLOOR)) {
                y += 1;
            }
            break;
        default:
            return stary_block;
    }


    stary_block = render_map[x][y][z];
    //render_map[character[0]][character[1]][character[2]] = stary_block;
    character[0].x = x;
    character[0].y = y;
    character[0].z = z;
    render_map[x][y][z] = B_PLAYER;
    return stary_block;
}