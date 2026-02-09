/*
Statek dyplomatyczny Orion One patroluje galaktykę w celu utrzymania pokoju i łagodzenia napięć społecznych. Kapitan statku codziennie otrzymuje dane o poziomie zadowolenia mieszkańców w różnych systemach planetarnych. 
Dane te są analizowane, aby podjąć decyzję, w którym regionie galaktyki potrzebna jest interwencja dyplomatyczna. Poziomy zadowolenia (w skali od 0 do MAKSYMALNA_ILOSC_DNI) zapisywane są w postaci dwuwymiarowej tablicy liczb całkowitych, w której wiersze odpowiadają poszczególnym systemom planetarnym a kolumny - kolejnym dniom pomiaru. Nazwy systemów przechowywane są w drugiej tablicy tekstowej.

Napisz program, który:

wczyta z klawiatury nazwy pięciu systemów planetarnych, {}
wypełni tablicę nastroje wartościami generowanymi według poniższego modelu:
Dla pierwszego dnia losuje poziom zadowolenia z przedziału 0-MAKSYMALNA_ILOSC_DNI.{}
Dla każdego kolejnego dnia oblicza wartość na podstawie poprzedniego pomiaru, dodając losowe odchylenie od -3 do +3.{}
Z niewielkim prawdopodobieństwem (np. 1 na 8) występuje nieoczekiwane zdarzenie, np. bunt, porozumienie pokojowe lub katastrofa, które powoduje gwałtowną zmianę nastrojów w danym systemie (od -30 do +30 punktów).{}
wyświetla dane w postaci tabeli:{}
po wyświetleniu tabeli program powinien udostępnić użytkownikowi menu, które pozwala analizować sytuację w galaktyce:
1. Oblicz średni poziom zadowolenia we wszystkich systemach{}
2. Wskaż system o najwyższym średnim poziomie zadowolenia{}
3. Wskaż system o najniższym średnim poziomie zadowolenia{}
4. Znajdź systemy, w których występują niepokoje (wartość < 40 w dowolnym dniu){}
5. Zaktualizuj dane o zadowoleniu (dodanie nowego dnia)
6. Wyświetl raport ponownie
0. Zakończ program

Po wybraniu opcji 5. program powinien:

przesunąć dane w tablicy tak, by najstarszy dzień został usunięty,
wygenerować nowy dzień pomiaru zgodnie z opisanym wcześniej algorytmem,
podać system, który odnotował największy spadek,
wyświetlić komunikat o konieczności interwencji dyplomatycznej, jeżeli średni poziom zadowolenia w którymś systemie spadł poniżej 20. */


//todo  5 - nowy_dzien()-> zle indeksowanie czy cos
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "data.h"
#include "analysis.h"
#include "display.h"

//Display.c na logike

int main(){
    //while (getchar() != '\n');
    int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI];// system planetarny / dzien
    int wybor = 0;
    int dzien = 0;
    char tablica_nazwy[ILOSC_SYSTEMOW][10] = {
    "Alderaan",
    "Tatooine",
    "Naboo",
    "Hoth",
    "Endor"
    };//system planetarny / ilosc znakow
    //puts("Podaj ILOSC_SYSTEMOW nazw systemw planetarnych");
    /*
    for(int i = 0;i < ILOSC_SYSTEMOW;i++){
        scanf("%19s", tablica_nazwy[i]);
        printf("\n");
    }
    */
   srand(time(NULL));
    for(int i = 0;i < ILOSC_SYSTEMOW;i++){
        tablica[i][0] = (rand() % 101);
    }
    for(int i = 0;i < ILOSC_SYSTEMOW;i++){
        for(int j = 1;j < MAKSYMALNA_ILOSC_DNI;j++){
            if(rand()%8 == 1){
                tablica[i][j] = tablica[i][j - 1] + (rand()% 60 - 30);
            }else{
                tablica[i][j] = tablica[i][j - 1] + (rand()% 6 - 3);
            }
        }
    }

    
    
    while(1){
        while (getchar() != '\n');
        raport(tablica_nazwy,dzien,tablica);
        menu();
        scanf("%d",&wybor);
        switch (wybor)
        {
        case 1:
            for(int i = 0;i < ILOSC_SYSTEMOW;i++){
            printf("Sredni wynik dla %10s to %4d\n",tablica_nazwy[i],sredni_poziom(tablica,i));
            }
            break;
        case 2:
            printf("Najwyzszy poziom zadowolenia to %d\n",max_zadowolenie(tablica));
            break;
        case 3:
            printf("Najnizszy poziom zadowolenia to %d\n",min_zadowolenie(tablica));
            break;
        case 4:
            puts("\n0 - Wartosci odpowiednie \n1 - Wartosc niepokojoca \n");
            for(int i = 0;i < ILOSC_SYSTEMOW;i++){
                printf("%10s -- %d\n",tablica_nazwy[i],niepokoje(tablica,i));
            }
            puts("\n");
            break;
        case 5:
            puts("Nowy dzien");
            nowy_dzien(tablica);
            break;
        case 6:
            raport(tablica_nazwy, dzien, tablica);
            break;
        case 0:
            exit(0);
            break;
            puts("\n");
            raport(tablica_nazwy,dzien,tablica);
            puts("\n");
        default:
            break;
        }
    }
    return 0;
}