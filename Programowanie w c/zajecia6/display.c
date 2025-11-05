#include <stdio.h>
#include "data.h"
#include "analysis.h"
void raport(char tablica_nazwy[ILOSC_SYSTEMOW][10],int dzien,int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]){
    for(int i = 0;i < ILOSC_SYSTEMOW;i++){
            // Ogarnąć na rozum
            enum DiplomacyStatus status = assessStatus(tablica, i, 1);
            const char *opis;
            switch(status){
                case STABLE:   opis = "STABLE";   break;
                case TENSE:    opis = "TENSE";    break;
                case CRITICAL: opis = "CRITICAL"; break;
                default:       opis = "UNKNOWN";  break;
        }
            printf("%20s -- %d -- %5s\n",tablica_nazwy[i],tablica[i][dzien + DZIEN_OFFSET],opis);
    }
}
void menu(void){
    puts("1. Oblicz średni poziom zadowolenia we wszystkich systemach");
    puts("2. Wskaż system o najwyższym średnim poziomie zadowolenia");
    puts("3. Wskaż system o najniższym średnim poziomie zadowolenia");
    puts("4. Znajdź systemy, w których występują niepokoje (wartość < 40 w dowolnym dniu)");
    puts("5. Zaktualizuj dane o zadowoleniu (dodanie nowego dnia)");
    puts("6. Wyświetl raport ponownie");
    puts("0. Zakończ program");
}