/*
Napisz program, który sprawdzi, czy dwie liczby podane przez użytkownika są parzyste, nieparzyste,
czy też jedna z nich jest parzysta, a druga nie.
 Komputer powinien na końcu wyświetlić odpowiedni komunikat, np. „Obie liczby są parzyste” albo „Jedna parzysta, druga nie”.*/


#include <stdio.h>

int main(){
    int a,b;
    printf("Podaj dwie liczby");
    scanf("%d",&a);
    scanf("%d",&b);
    if (a%2 == 0 && b %2 == 0){printf("Liczby są parzyste");}
    if (a%2 == 1 && b %2 == 1){printf("Liczby są nie parzyste");}
    if (a%2 == 0 && b %2 == 1){printf("Liczba a jest parzysta a liczba b nie jest parzysta");}
    if (a%2 == 1 && b %2 == 0){printf("Liczby a jest nie parzysta a liczba b jest parzysta");}
}