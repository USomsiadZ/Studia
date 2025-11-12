/*
eśli podana wartość jest mniejsza od zera lub większa niż 200 kilogramów, program powinien poinformować, że wprowadzono niepoprawną wagę.
Walizki mieszczące się w zakresie od 0 do 23 kilogramów są akceptowane bez dodatkowych opłat.
Jeżeli waga przekracza 23 kilogramy, ale nie jest większa niż 32 kilogramy, program powinien zgłosić konieczność dopłaty za nadbagaż.
W przypadku walizek cięższych niż 32 kilogramy należy wypisać komunikat, że nie mogą zostać przyjęte do odprawy.*/

#include <stdio.h>

int main(){
    int waga;
    printf("podaj wage bagazu");
    scanf("%d",&waga);
    if (waga > 200 || waga < 0){printf("Waga nie prawidlowa");}
    else if (waga >= 0 && waga <= 23){printf("Waga zaakceptowana bez dodatkowych opłat");}
    else if (waga > 23 && waga <= 32){printf("Waga zaakceptowana z dodatkowymi opłatami");}
    else {printf("Walizka nie moze zostac przyjeta");}
}