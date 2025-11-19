/*
Na skrzyżowaniu działa sygnalizacja świetlna. Światła zmieniają się cyklicznie zgodnie z kolejnością: GREEN → YELLOW → RED → GREEN → ...
Długość świecenia zielonego światła zależy od natężenia ruchu, które wprowadza użytkownik.

Zdefiniuj typ wyliczeniowy
Program wczytuje od użytkownika natężenie ruchu (liczba 0–100).
Na podstawie natężenia ruchu program ustala czas świecenia światła GREEN:
Natężenie ruchu	Czas trwania światła GREEN
≥ 70	40 sekund
40–69	25 sekund
< 40	15 sekund
Czas pozostałych świateł jest stały: YELLOW - 3 sekundy, RED - 10 sekund.
Program symuluje działanie sygnalizacji, wyświetlając aktualny stan:
GREEN (pozostało 24 s)
GREEN (pozostało 23 s)
...
YELLOW (pozostało 3 s)
...
RED (pozostało 10 s)
Po zakończeniu jednego cyklu program zaczyna kolejny (może wykonać np. 3 pełne cykle lub działać w pętli nieskończonej).
*/
#include <stdio.h>
enum DiplomacyStatus {
    GREEN,
    YELLOW,
    RED,
};

int main(){
    printf("Podaj natezenie ruchu");
    //scanf("%d",natezenie);
    for(int j = 0;j < 3;j++){
        for(int i = 0;i < 40;i++){
            printf("Green pozostalo %d sekund \n",40 - i);
        }
        for(int i = 0;i < 3;i++){
            printf("Yellow pozostalo %d sekund \n",3 - i);
        }
        for(int i = 0;i < 10;i++){
            printf("Red pozostalo %d sekund \n",10 - i);
        }
    }
    
}