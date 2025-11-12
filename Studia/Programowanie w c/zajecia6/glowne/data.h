#ifndef DATA_H
#define DATA_H
#define ILOSC_SYSTEMOW 5
#define MAKSYMALNA_ILOSC_DNI 100
#define DZIEN_OFFSET 50

void nowy_dzien(int tablica[ILOSC_SYSTEMOW][MAKSYMALNA_ILOSC_DNI]);

enum DiplomacyStatus {
    STABLE,
    TENSE,
    CRITICAL
};

#endif