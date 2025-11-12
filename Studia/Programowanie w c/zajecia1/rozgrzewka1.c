/*
Napisz program, który poprosi użytkownika o dwie liczby całkowite.
Następnie obliczy ich sumę i średnią arytmetyczną i poda wynik na ekranie.
*/
#include <stdio.h>

int main(){
    int a,b,suma;
    float srednia;
    printf("Podaj dwie liczby");
    scanf("%d",&a);
    scanf("%d",&b);
    suma = a + b;
    srednia = (a+b)/2.0 ;
    printf("Srednia to %f \n Suma to %d",srednia,suma);

}
    
    
    
    
    