/*Napisz program, który utworzy dwuwymiarową tablicę liczb całkowitych o wymiarach N × M (dla uproszczenia można przyjąć, że N, M < 10, zdefiniowane przy użyciu #define).
Następnie wypełnij tablicę w taki sposób, aby każda liczba odzwierciedlała swoje położenie:

* cyfra dziesiątek oznacza numer wiersza (liczony od 1),
* cyfra jedności oznacza numer kolumny (liczoną od 1).
Program powinien wyświetlić całą tablicę w formie czytelnej tabeli, w której każdy wiersz odpowiada jednemu wierszowi tablicy, a kolumny pokazują wartości poszczególnych pól.

Przykładowy wynik (dla N = 3, M = 4):

11 12 13 14
21 22 23 24
31 32 33 34*/
#include <stdio.h>
#define N 10 //wiersze
#define M 10 //kolumny

int main(){
    int tablica[N][M]; 
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            tablica[i][j] = (i+1) * 10 + (j+1);
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%3d ", tablica[i][j]);
        }
        printf("\n");
    }
}