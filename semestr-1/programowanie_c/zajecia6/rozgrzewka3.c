/*
W pewnym systemie rezerwacji przechowujemy listę nazw miast, w których znajdują się punkty obsługi klienta. Każda nazwa miasta zapisana jest jako osobny napis, a wszystkie nazwy przechowywane są wspólnie w jednej strukturze danych - dwuwymiarowej tablicy znaków, w której każdy wiersz reprezentuje jedno miasto.
Napisz program, który utworzy dwuwymiarową tablicę znaków przeznaczoną do przechowywania nazw maksymalnie 20 miast (dla uproszczenia przyjmij, że długość pojedynczej nazwy wynosi nie więcej niż 30 znaków).

Program powinien wczytać z klawiatury nazwy miast i wyświetlić pełną listę wszystkich wprowadzonych nazw. Przy wprowadzaniu zadbaj, by każda nazwa miasta zaczynała się od wielkiej litery.

Po wczytaniu i wyświetleniu zawartości tablicy:
* poproś użytkownika o wpisanie początkowych liter miasta (prefiksu),
* wypisz wszystkie miasta, których nazwy zaczynają się od podanego fragmentu - przy porównywaniu ignoruj wielkość liter (np. po wpisaniu "sz" mogą zostać znalezione "Szczecin" i "Szczawnica").
*/
#include <stdio.h>
#include <string.h>
#define MAX_MIASTA 20
#define MAX_ZNAKI 30
char lower(int tablica){
    int znak = tablica;
    int roznica = 'Z' - 'z';
    if(znak <= 'Z' && znak >= 'A'){
        znak = znak - roznica;
    }
    return znak;
}
int main(){
    char tablica_nazw[MAX_MIASTA][MAX_ZNAKI];
    int ilosc_miast = 0;
    char prefiks[MAX_ZNAKI];
    int war = 0;
    puts("Podaj ilosc miast. Maksymalnie 20");
    scanf("%d",&ilosc_miast);
    for(int i = 0;i < ilosc_miast;i++){
        while (getchar() != '\n');
        scanf("%29s",tablica_nazw[i]);
        if(!(tablica_nazw[i][0] <= 'Z' && tablica_nazw[i][0] >= 'A')){
            puts("Ma sie zaczynaj z wielkiej litery");
            i--;
        }
    }
    for(int i = 0;i < ilosc_miast;i++){
        printf("%29s\n",tablica_nazw[i]);
    }
    puts("Podaj prefiks miasta");
    scanf("%s",prefiks);
    int k = strlen(prefiks);

    for(int i = 0;i < ilosc_miast;i++){
        war = 0;
        for(int j = 0;j < k;j++){
        if(lower(tablica_nazw[i][j]) == lower(prefiks[j])){
            war = 1;
            break;
        };
    }
    if(war == 1){
        printf("%29s\n",tablica_nazw[i]);
    }
    }




}