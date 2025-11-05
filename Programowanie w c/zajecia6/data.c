#include <stdio.h>
#include <stdlib.h>
#include "data.h"
void nowy_dzien(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]){
    for(int j = 0;j< ILOSC_SYSTEMOW ;j++){
        for(int i = 0;i < MAKSYMALNA_ILOSC_DNI - 1;i++){
            tablica[j][i] = tablica[j][i + 1];
        }
    }
    for(int j = 0;j< ILOSC_SYSTEMOW ;j++){
        tablica[j][MAKSYMALNA_ILOSC_DNI - 1] = rand()%101;
    }

}