/*
W dziale kontroli jakości prowadzi się rejestr pomiarów z bieżącej produkcji. Wyniki są przechowywane w dynamicznej tablicy liczb całkowitych, którą na początku dnia uzupełniają operatorzy maszyn.
Czasami w zestawie występują wartości błędne, gdy urządzenie pomiarowe chwilowo zgłosiło zerowy lub ujemny odczyt. Takie wpisy należy usunąć z rejestru, aby nie zakłócały statystyk.
Napisz funkcję, która wyczyści tablicę z niepoprawnych wartości.
W programie głównym utwórz dynamiczną tablicę wpisów, wypełnij ją wartościami i wypisz na ekran. Następnie napraw jej zawartość i wypisz tablicę ponownie na ekran.

Powyższą funkcję zrealizuj na dwa sposoby: z wykorzystaniem realloc oraz samodzielnie tworząc nową tablicę.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void fill(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        tab[i] = rand()%201 - 101;
    }
}
void show(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\n",tab[i]);
    }
}

int *delete(int *tab,int *size,int index){
    for (int i = index; i < *size - 1; i++)
    {
        tab[i] = tab[i + 1];
    }
    int new_size = *size -1;
    int *p = realloc(tab,new_size * sizeof *tab);
    if(p) tab = p;
    *size = new_size;
    return tab;
}
int *scan_delete(int *tab,int *size){
    for (int i = 0; i < *size;)
    {
        if(tab[i] < 1){
            tab = delete(tab,size,i);
        }else{
            i++;
        }
    }
    return tab;
}
int main(){
    int size = 5;
    int *tab = malloc(size * sizeof *tab);
    srand(time(NULL));
    fill(tab,size);
    show(tab,size);
    printf("-------\n");
    tab = scan_delete(tab,&size);
    show(tab,size);
    free(tab);
    return 0;
}