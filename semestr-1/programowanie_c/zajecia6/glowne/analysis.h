#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "data.h"

int niepokoje(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI], int system);
int sredni_poziom(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI],int system);
int min_zadowolenie(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]);
int max_zadowolenie(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]);
enum DiplomacyStatus assessStatus(const int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI], int systemIndex, int days);
#endif