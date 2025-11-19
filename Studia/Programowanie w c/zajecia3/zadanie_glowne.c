/*
Po uruchomieniu systemu należy wprowadzić liczbowy kod kapitana. Tylko jeden kod jest poprawny.
Po błędnym kodzie wyświetlany jest komunikat o nieudanej próbie logowania wraz z informacją, ile prób (z trzech możliwych) jeszcze pozostało.
Po trzech nieudanych próbach wyświetlany jest odpowiedni komunikat i program kończy działanie.
Po poprawnym logowaniu system wyświetla menu:
1 – Charge the reactor core: wczytaj dodatnią wartość i dodaj ją do poziomu energii.
2 – Discharge the reactor core: wczytaj wartość i odejmij od poziomu energii (jeśli wystarczająca).
3 – Check energy level: wyświetl aktualny poziom energii.
0 – Log out: powrót do logowania (poziom energii jest zapamiętywany przez cały czas działania programu).
Jeśli użytkownik wybierze niedostępną opcję (np. 4), program powinien o tym poinformować i ponownie wyświetlić menu.
Każdorazowo system wyświetla informację, czy operacja została wykonana prawidłowo czy też nie (ujemna wartość energii, lub zbyt duża wartość zużycia)
Dodatkowo system jest zabezpieczony przed podaniem wartości energii innej niż liczbowa - w takiej sytuacji wyświetla komunikat i ponawia wczytanie wartości (do skutku).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int logowanie(){
    int kod_kapitana;
    int ilosc_pozostalych_prob = 3;
    printf("Podaj kod kapitana\n");
    scanf("%d",&kod_kapitana);
    while (kod_kapitana != 1234){
        ilosc_pozostalych_prob--;
        
        while (getchar() != '\n'); 
        
        if (ilosc_pozostalych_prob != 0){
            printf("Pozostalo %d prob\n",ilosc_pozostalych_prob);
        }
        else{
            printf("Koniec programu");
            exit(0);
        }
    
    }
    return 1;
}
int menu(){
    int wybor;
    int energia;
    int wartosc;

    srand(time(NULL));
    energia = rand()%100 + 1;
    
    printf("1 – Charge the reactor core: wczytaj dodatnią wartość i dodaj ją do poziomu energii.\n");
    printf("2 – Discharge the reactor core: wczytaj wartość i odejmij od poziomu energii (jeśli wystarczająca).\n");
    printf("3 – Check energy level: wyświetl aktualny poziom energii.\n");
    printf("0 – Log out: powrót do logowania (poziom energii jest zapamiętywany przez cały czas działania programu).\n");
    while(1){
    while (getchar() != '\n'); 
    scanf("%d",&wybor);
    if (wybor == 1){
        scanf("%d",&wartosc);
        if (wartosc>0){
            energia = energia + wartosc;
            if(energia > 100){
            printf("Energia jest za duza");
            energia = energia - wartosc;}
        }
        else{
            printf("wartosc nie jest dodatnia\n");
        }
        
    }
    else if (wybor == 2){
                scanf("%d",&wartosc);
                energia = energia - wartosc;
                if(energia < 0){
                printf("Energia jest za mała\n");
                energia = energia + wartosc;}
    }
    else if (wybor == 3){
        printf("Wartość energi %d\n",energia);
    }
    else if (wybor == 0){
        logowanie();
    }
    else if (!(wybor >0 && wybor <3)){
        printf("Wybor nie jest poprawny albo wprowadzono nie poprawną liczbe\n");
    }
    }
}
int main(){

    logowanie();
    menu();

}