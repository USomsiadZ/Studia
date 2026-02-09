/*
Tylko jedno zaklęcie może zwyciężyć w tej krótkiej walce — ogień topi lód, lód zatrzymuje błyskawicę, 
a błyskawica rozprasza ogień. Jeśli obaj czarodzieje wybiorą tę samą moc, 
energia zderzy się i pojedynek zakończy się remisem.

Twoim zadaniem jest napisać program w języku C, który przeprowadzi taki pojedynek.
Gracz powinien wprowadzić swój wybór, a komputer wylosować zaklęcie.
Program powinien następnie wyświetlić oba wybory i ogłosić wynik starcia.
Ogień > lod , lod > blyskawica, blyskawica > ogien
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{

    int wybor_gracz,wybor_komputer;
    printf(" Ogien > lod , lod > byskawica, blyskawica > ogien \n");
    printf("wybierz moc \n 1: ognista kula \n 2: Lodowa Strzala \n 3: Blyskawica\n");
    scanf("%d",&wybor_gracz);
    srand(time(NULL));
    wybor_komputer = rand()%3+1;

    if (wybor_gracz == 1){printf("Wybor gracza to ogien\n");}
    if (wybor_gracz == 2){printf("Wybor gracza to lod\n");}
    if (wybor_gracz == 3){printf("Wybor gracza to blyskawica\n");}
    if (wybor_komputer == 1){printf("Wybor komputer to ogien\n");}
    if (wybor_komputer == 2){printf("Wybor komputer to lod\n");}
    if (wybor_komputer == 3){printf("Wybor komputer to blyskawica\n");}

    if (wybor_gracz == 1){
        if(wybor_komputer == 1)
            printf("remis");
        if(wybor_komputer == 2)
            printf("wygrana");
        if(wybor_komputer == 3)
            printf("przegrana");}
    else if (wybor_gracz == 2){
        if(wybor_komputer == 1)
            printf("przegrana");
        if(wybor_komputer == 2)
            printf("remis");
        if(wybor_komputer == 3)
            printf("wygrana");}
    else if (wybor_gracz == 3){
        if(wybor_komputer == 1)
            printf("wygrana");
        if(wybor_komputer == 2)
            printf("przegrana");
        if(wybor_komputer == 3)
            printf("remis");}


}


