/*
Statek kosmiczny Orion One otrzymuje od Centrali Nawigacyjnej pliki tekstowe zawierające listę galaktycznych współrzędnych punktów, które mogą wymagać odwiedzenia. W pliku znajdują się wartości rzeczywiste zapisane w dowolnej liczbie wierszy, oddzielone białymi znakami. Kolejne dwie liczby tworzą jedną parę współrzędnych galaktycznych: długość oraz szerokość. Ponieważ dane pochodzą z wielu stacji obserwacyjnych i mogą nie mieć idealnej struktury, program powinien najpierw sprawdzić, czy plik jest poprawny, to znaczy, czy zawiera wyłącznie liczby rzeczywiste oraz czy ich liczba jest parzysta, tak aby można było poprawnie utworzyć wszystkie pary współrzędnych.

Jeśli plik przejdzie weryfikację, program wczytuje wszystkie współrzędne do dynamicznej tablicy i wyświetla je użytkownikowi. Kapitan statku podaje następnie bieżącą pozycję Oriona One oraz promień działania pokładowego radaru. Program oblicza odległość każdego punktu od pozycji statku i usuwa z listy te miejsca, które znajdują się poza zasięgiem radaru, pozostawiając jedynie te, które statek może realnie odwiedzić.

Po przefiltrowaniu danych program zapisuje pozostałe współrzędne do pliku binarnego w formacie nieczytelnym dla człowieka.

Celem zadania jest napisanie programu, który przeprowadza cały powyższy proces. Program powinien prawidłowo zarządzać pamięcią dynamiczną i być odporny na błędne dane wejściowe. Na potrzeby realizacji zadania można wykorzystać własną strukturę, reprezentującą pojedynczy punkt galaktyczny.
*/
#define ILOSC_DANYCH 10
#include <stdio.h>
FILE *open_file(char *plik){
    FILE *f = fopen(plik, "r");
    if (!f) {
        puts("Błąd odczytu");
    }
    return f;
}
struct koordytany{
        int x;
        int y;
    };
void close_file(FILE *f){
    if(f)fclose(f);
    }
int x_y(FILE *f){
    int ch;
    int liczba = 0;
    while (1){
        if ((ch = fgetc(f)) != ' ' && ch != EOF && ch != '\n' && (ch > '0' || ch < '9'))
        {
            liczba = liczba * 10 ;
            liczba += (ch - '0');
        }else if(ch == EOF){
            return -1;
            break;
        }else{
            break;
        }
        
        //else if(ch == EOF){
            //return liczba = -1;
        //}
        

    }

    return liczba;
}
int main(){
    FILE *f = open_file("/Users/hubert/GitHub/Nauka/studia/programowanie_c/zajecia9/output/data.txt");
    struct koordytany kor[ILOSC_DANYCH];
    for (size_t i = 0; i < ILOSC_DANYCH; i++)
    {
        kor[i].x = x_y(f);
        kor[i].y = x_y(f);
    }
    for (size_t i = 0; i < ILOSC_DANYCH; i++)
    {
        printf("%d\n",kor[i].x);
        printf("%d\n",kor[i].y);
    }
    




    close_file(f);
    return 0;
}

