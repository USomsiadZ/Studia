/*
Umiejętność określania liczby cyfr przydaje się m.in. przy walidacji danych (np. numerów PESEL, PIN, telefonów),
formatowaniu wyników oraz analizie struktur liczbowych w algorytmach, które operują na poszczególnych cyfrach.
Napisz program, który wczytuje od użytkownika liczbę całkowitą i oblicza, z ilu cyfr się składa.
Program powinien poprawnie działać także dla liczb ujemnych (np. dla -1234 wynik to 4).
*/
#include <stdio.h>

int main(){
    int liczba;
    int liczba_cyft;
    while(liczba_cyft != 0){
        liczba = liczba/10;
        liczba++;
    }
}
