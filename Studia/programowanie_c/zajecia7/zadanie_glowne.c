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
// 1) Usuwanie z tablicy wszystkich wystąpień wskazanej wartości.
// 2) Zwiększanie rozmiaru tablicy i dopisywanie dodatkowych odczytów czujników.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int min(int *tab,int size){
    int min = *tab;
    for (int i = 0; i < size; i++)
    {
        min = (min>*(tab+i)) ? *(tab+i) : min;
    }
    return min;
}
int max(int *tab,int size){
    int max = *tab;
    for (int i = 0; i < size; i++)
    {
        max = (max<*(tab+i)) ? *(tab+i) : max;
    }
    return max;
}
void show(int *tab, int size){
    for (int i = 0; i < size; i++)
        {
            printf("%d\n",*(tab + i));
        }
    printf("\n");
    }
void fill_tab(int *tab,int size,int from){
    for (int i = from; i < size; i++)
    {
        *(tab + i) = rand()% 10;
    }
}
int over_value(int *tab,int size,int value){
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if(*(tab + i) > value)count++;
    }
    return count;
}
int *new_tab_over_value(int *tab,int *size,int value){
    int count = over_value(tab,*size,value);
    int *p = realloc(tab,*size*sizeof(int));
    int j = 0;
    tab = p ? p : tab;
    for (int i = 0; i < *size; i++)
    {
        if(*(tab + i) > value) *(p + j++) = *(tab + i);
    }
    *size = count;
    return p;
}
void rm_value_tab(int *tab,int *size,int value){
    for (int i = 0; i < *size; i++)
    {
        if(*(tab + i) == value){
            *size = *size -1;
            for (int j = i; j < *size; j++)
            {
                *(tab +j) = *(tab + j + 1);
            }
        }
    }

}
int *add_tab(int *tab,int *size,int new){
    int *p = tab;
    p = realloc(tab,(*size + new) * sizeof(int));
    tab = p ? p : tab;
    fill_tab(p,*size + new,*size);
    *size = *size + new;
    return tab;
}
// alokacji, zwalniania pominięte

int main(){
    int size;
    srand(time(NULL));
    printf("Podaj wielkosc tablicy: ");
    scanf("%d",&size);
    int *tab = malloc(size * sizeof(int));
    if(!tab){
        fprintf(stderr,"Blad alokacji pamieci.\n");
        return 1;
    }

    fill_tab(tab,size,0);

    int running = 1;
    while(running){
        int opcja;
        printf("\n=== Menu danych telemetrycznych ===\n");
        printf("1. Wyswietl tablice\n");
        printf("2. Wypelnij tablice losowo\n");
        printf("3. Pokaz min i max\n");
        printf("4. Policz ile wartosci > prog\n");
        printf("5. Utworz tablice z wartosci > prog\n");
        printf("6. Usun wskazana wartosc\n");
        printf("7. Dodaj nowe odczyty\n");
        printf("0. Wyjscie\n");
        printf("Twoj wybor: ");
        scanf("%d", &opcja);

        switch(opcja){
            case 1:
                show(tab,size);
                break;
            case 2:
                fill_tab(tab,size,0);
                printf("Tablica zostala ponownie wypelniona.\n");
                break;
            case 3:
                printf("Min: %d, Max: %d\n", min(tab,size), max(tab,size));
                break;
            case 4: {
                int prog;
                printf("Podaj prog: ");
                scanf("%d", &prog);
                printf("Liczba wartosci > %d: %d\n", prog, over_value(tab,size,prog));
                break;
            }
            case 5: {
                int prog;
                printf("Podaj prog: ");
                scanf("%d", &prog);
                tab = new_tab_over_value(tab,&size,prog);
                printf("Nowa tablica zawiera %d elementow.\n", size);
                break;
            }
            case 6: {
                int value;
                printf("Podaj wartosc do usuniecia: ");
                scanf("%d", &value);
                rm_value_tab(tab,&size,value);
                printf("Aktualny rozmiar: %d\n", size);
                break;
            }
            case 7: {
                int extra;
                printf("Ile nowych odczytow dodac: ");
                scanf("%d", &extra);
                if(extra > 0){
                    tab = add_tab(tab,&size,extra);
                    printf("Nowy rozmiar: %d\n", size);
                }
                break;
            }
            case 0:
                running = 0;
                break;
            default:
                printf("Nieznana opcja. Sprobuj ponownie.\n");
        }
    }

    free(tab);
    return 0;
}