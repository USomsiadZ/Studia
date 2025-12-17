/*
W pewnym dziale technicznym prowadzony jest prosty rejestr zgłoszeń serwisowych. Każde zgłoszenie ma przypisany numer (liczbę całkowitą). Numery zgłoszeń są przechowywane w tablicy dynamicznej.
Napisz funkcję int* findTicket(int *tab, int size, int ticketId);, która wyszuka konkretne zgłoszenie i zwróci adres miejsca, w którym się ono znajduje. W przypadku braku zgłoszenia o podanym id, funkcja zwraca NULL.
W programie głównym utwórz dynamiczną tablicę i wypełnij ją numerami zgłoszeń. Następnie zaprezentuj działanie stworzonej funkcji.
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 7
int* findTicket(int *tab, int size, int ticketId){
    for (int i = 0; i < size; i++)
    {
        if(ticketId == tab[i]){
            return &tab[i];
        }
    }
    return NULL;
}
void fill(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        tab[i] = i + i * 10;
    }
}
void show(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        printf("%2d -- %p\n",tab[i],&tab[i]);
    }
}

int main(){
    int *tab = malloc(SIZE * sizeof(int));
    fill(tab,SIZE);
    show(tab,SIZE);
    printf("\n%2d -- %p\n",*findTicket(tab,SIZE,33),findTicket(tab,SIZE,33));

    free(tab);
    tab = NULL;
    return 0;
}