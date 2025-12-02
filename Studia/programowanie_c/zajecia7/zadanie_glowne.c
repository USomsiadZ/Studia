/*
Statek kosmiczny Orion One przemierza obszar gęstej mgławicy, która zakłóca systemy czujników. Aby utrzymać stabilność statku, inżynierowie muszą przygotować Moduł Diagnostyczny, który będzie analizował surowe dane telemetrii i dynamicznie zarządzał ich pamięcią.
Dane telemetrii są reprezentowane jako zestaw liczb całkowitych, które opisują aktualny stan różnych podsystemów pokładowych.
Stwórz zestaw funkcji do obsługi, analizy i modyfikacji tych danych.
Program ma umożliwiać:

* Tworzenie dynamicznej tablicy telemetrii o rozmiarze podanym przez operatora.{}
* Wypełnianie tablicy danymi (pobranymi z wejścia lub losowymi).{}
* Wyświetlanie tablicy telemetrii, przy użyciu iteracji wskaźnikowej.{}
* Analizę danych telemetrii, obejmującą:
    * wyznaczenie wartości minimalnej i maksymalnej,{}
    * obliczenie średniej{}
    * wyznaczenie liczby wartości powyżej zadanego progu,{}
    * stworzenie nowej dynamicznej tablicy zawierającej wyłącznie wartości przekraczające zadany próg (funkcja ma zwrócić nową tablicę i jej rozmiar).{}
* Usuwanie z tablicy wszystkich wystąpień wskazanej wartości.{}
* Zwiększanie rozmiaru tablicy i dopisywanie dodatkowych odczytów czujników.{}
* Wszystkie operacje alokacji, zwalniania, powiększania i filtrowania muszą być zrealizowane w osobnych funkcjach.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int min(int *tab,int rozmiar){
    int min;
    for (int i = 0; i < rozmiar; i++)
    {
        if(min > tab[i])min = tab[i];
    }
    return min;

}
int max(int *tab,int rozmiar){
    int max = tab[0];
    for (int i = 0; i < rozmiar; i++)
    {
        if(max < tab[i])max = tab[i];
    }
    return max;

}
int srednia(int *tab,int rozmiar){
    int suma = 0;
    for (int i = 0; i < rozmiar; i++)
    {
        suma += tab[i];
    }
    return suma/rozmiar;

}
int liczba_powyzej(int *tab,int rozmiar,int prog){
    int suma = 0;
    for (int i = 0; i < rozmiar; i++)
    {
        if(tab[i] >= prog)suma++;
    }
    return suma;

}
int *nowa_tablicy(int *tab,int rozmiar,int prog){
    int rozmiar_nowy = liczba_powyzej(tab,rozmiar,prog);
    int *tab_nowy = malloc((rozmiar_nowy + 1) * sizeof(int));
    tab_nowy[0] = rozmiar_nowy;
    int indeks = 1;
    for (int i = 0; i < rozmiar; i++) {
        if (tab[i] >= prog) tab_nowy[indeks++] = tab[i];
    }
    return tab_nowy;
}
int usun_wartosc(int *tab, int rozmiar, int wartosc){
    int nowy = 0;
    for (int i = 0; i < rozmiar; ++i)
        if (tab[i] != wartosc)
            tab[nowy++] = tab[i];
    return nowy;
}
void wypelnij_losowo(int *tab, int rozmiar){
    for (int i = 0; i < rozmiar; ++i) {
        tab[i] = rand() % 100;
    }
}

void wypisz_wskaznikiem(const int *tab, int rozmiar){
    for (const int *p = tab; p < tab + rozmiar; ++p) {
        printf("%d\n", *p);
    }
}

int *powieksz_tablice(int *tab, int stary_rozmiar, int dodatkowe){
    int nowy_rozmiar = stary_rozmiar + dodatkowe;
    int *nowa = realloc(tab, nowy_rozmiar * sizeof(int));
    return nowa;
}

int main(){
    int rozmiar_tablicy, usuwana_wartosc, prog = 20, wybor = -1;
    int *tablica_nowa = NULL;

    srand(time(NULL));
    puts("Podaj wielkosc tablicy");
    scanf("%d",&rozmiar_tablicy);

    int *tab = malloc(rozmiar_tablicy * sizeof(int));
    wypelnij_losowo(tab, rozmiar_tablicy);

    while (wybor != 0) {
        puts("\n1-wypisz\n2-min\n3-max\n4-srednia\n5-liczba >= prog\n6-filtruj >= prog\n7-usun wartosc\n8-powieksz\n0-wyjscie");
        scanf("%d",&wybor);

        switch (wybor) {
            case 1:
                wypisz_wskaznikiem(tab, rozmiar_tablicy);
                break;
            case 2:
                printf("Min : %d\n", min(tab, rozmiar_tablicy));
                break;
            case 3:
                printf("Max : %d\n", max(tab, rozmiar_tablicy));
                break;
            case 4:
                printf("Srednia : %d\n", srednia(tab, rozmiar_tablicy));
                break;
            case 5:
                printf("Ilosc liczb powyzej >= %d : %d\n", prog, liczba_powyzej(tab, rozmiar_tablicy, prog));
                break;
            case 6:
                free(tablica_nowa);
                tablica_nowa = nowa_tablicy(tab, rozmiar_tablicy, prog);
                printf("Rozmiar nowej : %d\n", tablica_nowa[0]);
                for (int i = 1; i <= tablica_nowa[0]; ++i)
                    printf("%d\n", tablica_nowa[i]);
                break;
            case 7:
                printf("Podaj wartosc do usuniecia: ");
                scanf("%d",&usuwana_wartosc);
                rozmiar_tablicy = usun_wartosc(tab, rozmiar_tablicy, usuwana_wartosc);
                break;
            case 8: {
                int dodatkowe;
                printf("Ile elementow dodac: ");
                scanf("%d", &dodatkowe);
                tab = powieksz_tablice(tab, rozmiar_tablicy, dodatkowe);
                for (int i = rozmiar_tablicy; i < rozmiar_tablicy + dodatkowe; ++i)
                    tab[i] = rand() % 100;
                rozmiar_tablicy += dodatkowe;
                break;
            }
        }
    }

    free(tablica_nowa);
    free(tab);
    return 0;
}