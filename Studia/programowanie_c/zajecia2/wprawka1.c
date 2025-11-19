/*
Napisz program, który wylosuje temperaturę w zakresie od –10 do +35 stopni Celsjusza.
Następnie wyświetli komunikat z prognozą pogody, np.:

jeśli temperatura jest poniżej 0 → „Mróz! Ubierz się ciepło.”
jeśli temperatura mieści się od 0 do 25 → „Całkiem przyjemnie.”
jeśli temperatura jest powyżej 25 → „Upał! Szukaj cienia.”
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    int temperatura;
    srand(time(NULL));
    temperatura = rand()%45 -10;
    if (temperatura < 0){printf("Mróz! Ubierz się ciepło");}
    else if (temperatura <= 25){printf("Całkiem przyjemnie.");}
    else {printf("Upał! Szukaj cienia.");}
}