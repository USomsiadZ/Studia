/*
W niektórych konwersjach liczbowych (np. z systemu dziesiętnego na binarny, ósemkowy lub szesnastkowy) pierwszym etapem jest odwracanie liczby.
Napisz program, który wczyta liczbę całkowitą, a następnie wypisze ją "od tyłu", np. z 1234 → 4321.
*/

#include <stdio.h>
void wypisz(int tablica[],int miejsce){
    for(int l=0;l < miejsce;l++){
        char rr;
        int i = miejsce - l -1 ;
        if(tablica[i] < 10){
        printf("%d",tablica[i]);
        }else{
            int j = tablica[i];
            rr = 'a' + j -10;
            printf("%c",rr);

        }
    }
    printf("\n");
}
int potega(int x,int p){
    int liczba = x;
    if(p == 0)return 1;
    for(int i = 0;i < p;i++){
        liczba *= x;
    }
    return liczba;
}
void to_base(int liczba,int base){
    int tablica[128];
    int r;
    int i;
    for(i=0;liczba != 0;i++){
        r = liczba % base;
        liczba /= base;
        tablica[i] = r;
    }
    wypisz(tablica,i);
    return;
}

int main(){
    //1234(10) -> 10011010010(2)
    //1234(10) -> 2322(8)
    //1234(10) -> 4d2(8)
    int liczba = 1234;
    to_base(liczba,2);
    to_base(liczba,8);
    to_base(liczba,16);
        
}