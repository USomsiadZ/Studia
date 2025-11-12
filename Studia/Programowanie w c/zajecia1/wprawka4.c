/*
Napisz program, który pomoże wybrać odpowiedni typ autobusu dla podanej liczby pasażerów.
Do wyboru są dwa modele: pierwszy ma rzędy trzyosobowe (układ 1+2), a drugi rzędy pięcioosobowe (układ 2+3). 
Program powinien sprawdzić, czy pasażerowie mieszczą się dokładnie w którymś z autobusów. 
Jeśli nie, należy obliczyć, ile miejsc pozostanie pustych w każdym przypadku i wskazać ten wariant, w którym marnuje się mniej miejsc. 
Jeżeli oba rozwiązania są równie dobre, program powinien to zakomunikować.
(rzad - (pasazerowie % rzad)) % rzad
*/
#include <stdio.h>
int main(){
    int pasazerowie;
    printf("Podaj liczbe pasazerow");
    scanf("%d",&pasazerowie);
    if ((3 - (pasazerowie % 3)) % 3 < (5 - (pasazerowie % 5)) % 5){printf("Autobus z trzema miejscami jest lepszy");}
    else if ((3 - (pasazerowie % 3)) % 3 > (5 - (pasazerowie % 5)) % 5){printf("Autobus z piecioma miejscami jest lepszy");}
    else {printf("Oba autobusy są dobre");}
}