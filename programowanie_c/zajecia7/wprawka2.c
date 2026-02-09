/*
Problem wyszukiwania wszystkich wartości w zbiorze spełniających dane kryterium może mieć wiele zastosowań (np. wyszukiwanie wszystkich wystąpień danego słowa w dokumencie). Zrealizuj prostszy wariant tego problemu, oparty na liczbach całkowitych. Napisz funkcję, która znajdzie wszystkie wystąpienia określonej wartości w tablicy liczb całkowitych i zwróci tablicę indeksów, pod którymi się one znajdują. Pamiętaj o tym, że poza funkcję należy również wynieść rozmiar nowej tablicy (nie używaj zmiennych globalnych).
Przykład:
tablica wejściowa: {1, 3, 6, 2, 5, 6, 3, 5}
wartość szukana: 6
wynik funkcji to tablica: {2, 5}.
*/


#include <stdio.h>
#include <stdlib.h>
void fill(int *tab,int size){
    for (int i = 0; i < size/2; i++)
    {
        tab[i] = i + 1 + (i + 1) * 10;
        tab[i + size/2] = i + 1 + (i + 1) * 10;
    }
}
void show(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\n",tab[i]);
    }
}
void show_ad(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        printf("%p\n",(tab + i));
    }
}

int count_value(int *tab,int size,int value){
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += (tab[i] == value) ? 1 : 0;
    }
    return sum;
}
int *value_id(int *tab,int size,int *new_size,int value){
    int i;
    int j = 0;
    *new_size = count_value(tab,size,value);
    int *p = malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
    {
        if(tab[i] == value){
            p[j] = i;
            j++;
        }
        
    }
    return p;
}
int main(){
    int size = 6;
    int new_size = 0;
    int *tab = malloc(size * sizeof *tab);
    int *p;
    fill(tab,size);
    printf("-------\n");
    show(tab,size);    
    printf("-------\n");
    p = value_id(tab,size,&new_size,11);
    show(p,new_size);
    return 0;
}