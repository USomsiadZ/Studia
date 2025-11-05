#include "analysis.h"
#include "data.h"
int niepokoje(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI], int system){
    for(int i = 0; i < MAKSYMALNA_ILOSC_DNI - DZIEN_OFFSET; i++){
        if(tablica[system][i + DZIEN_OFFSET] < 40){
            return 1;
        }
    }
    return 0;
}
int sredni_poziom(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI],int system){
    int srednia = 0;
    for(int i = 0;i < MAKSYMALNA_ILOSC_DNI - DZIEN_OFFSET;i++){
        srednia += tablica[system][i + DZIEN_OFFSET];
    }
    return srednia/MAKSYMALNA_ILOSC_DNI;

}
int min_zadowolenie(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]){
    int min = 101;
    for(int i = 0;i < ILOSC_SYSTEMOW;i++){
        int srednia = sredni_poziom(tablica,i);
        if(min > srednia)min = srednia;
    }
    return min;
}
int max_zadowolenie(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]){
    int max = -1;
    for(int i = 0;i < ILOSC_SYSTEMOW;i++){
        int srednia = sredni_poziom(tablica,i);
        if(max < srednia)max = srednia;
    }
    return max;
}
enum DiplomacyStatus assessStatus(const int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI], int system, int days){
    // Dzien zaczyna sie na index 50 
    /*
    Status zależy np. od średniej z ostatnich X dni:
    ≥ 60 → STABLE
    40–59 → TENSE
    < 40 → CRITICAL
    */
   // todo teraz
   float suma = 0;
   for(int i = 0;i < days;i++){
    suma += tablica[system][i + DZIEN_OFFSET];
   }
   suma /= days;
   if(suma >= 60){
    return STABLE;
   }else if (suma < 40)
   {
    return CRITICAL;
   }else{
    return TENSE;
   }
   
}