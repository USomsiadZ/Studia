/*
W niektórych konwersjach liczbowych (np. z systemu dziesiętnego na binarny, ósemkowy lub szesnastkowy) pierwszym etapem jest odwracanie liczby.
Napisz program, który wczyta liczbę całkowitą, a następnie wypisze ją "od tyłu", np. z 1234 → 4321.
*/

#include <stdio.h>
int dlugosc(int x){
    int a = 1;
    while(x!=0){
    x = x / 10;
    a++;
    }
    return a;
}
int czy_parzysta(int x){
    int a = dlugosc(x);
    if (a % 2 == 0){
        //printf("Parzyste");
        return 1;
    }
    else{
        //printf("nie parzyste");
        return 0;
    }

}
int potega(int a,int potega){
    int podstawa;
    if(potega == 0){return 1;}
    podstawa = a;
    for (int i = 0; i < potega - 1;i++){
        a = podstawa * a;
    }
    return a;
}
int zamiana_parzyste(int liczba){
    int liczba2 = 0;
    int dlugosc_mod = 4;
    int pomocnicza;
    int miejsce = 0;
    while(miejsce < dlugosc_mod){
        pomocnicza = liczba % (10 * dlugosc_mod + 1);
        liczba2 = liczba2 + pomocnicza * potega(10,miejsce);
        miejsce++;
    }

    printf("Liczba : %d\n",pomocnicza);
    printf("Liczba : %d\n",liczba2);
    
    
    

}

int main(){
    int liczba = 1234;
    zamiana_parzyste(liczba);
    
    
}