/*
Pewna konstrukcja składa się z warstw modułów ułożonych jedna na drugiej.
Pierwsza (dolna) warstwa zawiera 15 modułów, a każda kolejna ma o jeden mniej od poprzedniej.
Każdy moduł waży 2 jednostki. Napisz program, który oblicza całkowitą masę konstrukcji, czyli sumę mas wszystkich modułów we wszystkich warstwach.
*/

#include <stdio.h>

int main(){
    int liczba_modolow = 15;
    int calkowita_masa = 0;
    while(liczba_modolow>0){
        calkowita_masa = calkowita_masa+(liczba_modolow*2);
        liczba_modolow--;
    }
    printf("%d",calkowita_masa);
}