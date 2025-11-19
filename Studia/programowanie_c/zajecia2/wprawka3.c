/*
Użytkownik wybiera rodzaj biletu spośród dostępnych opcji, na przykład bilet normalny za 4 zł lub ulgowy za 2 zł,
a następnie podaje liczbę biletów, które chce kupić.
Program oblicza łączną cenę zakupu i prosi użytkownika o wprowadzenie kwoty zapłaty.
Jeśli wprowadzona kwota jest dokładnie równa cenie biletów, program wyświetla komunikat o wydaniu biletów.
Jeżeli kwota jest większa, automat informuje o wydaniu reszty.
W przypadku, gdy użytkownik poda mniej pieniędzy niż wynosi cena, program wypisuje komunikat, że kwota jest niewystarczająca i bilety nie zostaną wydane.*/
#include <stdio.h>
int main(){
    int rodzaj,ilosc,cena,laczna_cena,kwota_wplacenia,reszta;
    printf("Wybieź rodzaj biletu\n 1: normalny - 4zł \n 2: ulgowy - 2zł\n");
    scanf("%d",&rodzaj);
    printf("Podaj ilosc biletow\n");
    scanf("%d",&ilosc);
    if (rodzaj == 1){cena = 4;}
    else if (rodzaj == 2){cena = 2;}
    else printf("Podano nie prawidlowy rodzaj biletu\n");
    laczna_cena = cena * ilosc;
    printf("Łączna kwota wynosi: %d\n Podaj ile wpłacasz \n",laczna_cena);
    scanf("%d",&kwota_wplacenia);
    reszta = kwota_wplacenia - laczna_cena;
    if (kwota_wplacenia == laczna_cena){printf("Trwa drukowanie biletu");}
    else if (kwota_wplacenia < laczna_cena){printf("Za mała kwota");}
    else if (kwota_wplacenia > laczna_cena){printf("Automat wydaje reszte w wysokości %d",reszta);}
    else {printf("Bląd");}
    

}