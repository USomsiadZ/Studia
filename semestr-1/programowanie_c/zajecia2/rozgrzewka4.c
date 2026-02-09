/*
Napisz program, który symuluje rzut kostką o dowolnej liczbie ścian.
Najpierw użytkownik podaje, ile ścian ma mieć kostka (np. 4, 6, 10, 20…), 
a następnie komputer losuje wynik od 1 do podanej liczby i wyświetla go na ekranie.*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main(){
    int sciany,wynik;
    printf("Podaj ilosc scian");
    scanf("%d",&sciany);
    srand(time(NULL));
    wynik = rand()%sciany+1;
    printf("Ilosc scian %d",wynik);

}