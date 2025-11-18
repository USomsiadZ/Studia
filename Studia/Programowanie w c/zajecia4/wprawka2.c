/*
W grze planszowej gracz steruje jednym pionkiem, który musi dotrzeć z górnego do dolnego rzędu planszy, unikając przeszkód. Plansza ma wymiary 5×5 i przechowywana jest w postaci dwuwymiarowej tablicy znaków.
Napisz program, który utworzy tablicę i przygotuje rozgrywkę według poniższych zasad:
* Wszystkie pola planszy są początkowo puste (oznaczone znakiem '.'). {}
* W pierwszym wierszu (górnym) w losowej kolumnie umieszczony jest pionek gracza, oznaczony znakiem 'P'.{}
* W środkowych wierszach (od drugiego do czwartego) program losowo rozmieszcza kilka przeszkód oznaczonych znakiem '#'. Przeszkody nie mogą pojawić się w pierwszym ani w ostatnim wierszu ani na polach zajętych przez pionki.
* W ostatnim wierszu znajduje się strefa celu - miejsca, do których gracz ma doprowadzić pionek.

Następnie program umożliwia wykonywanie ruchów według poniższych zasad:
* Gracz podaje kierunek ruchu (W - w lewo, E - w prawo, N - w górę, S - w dół).
* Pionek może poruszyć się o jedno pole w wybranym kierunku, jeśli pole docelowe jest puste ('.') i znajduje się w granicach planszy.
* Jeśli na polu docelowym znajduje się przeszkoda ('#'), program powinien wyświetlić komunikat.
Program po każdym ruchu wyświetla stan planszy i pyta, czy gracz chce wykonać następny ruch. 
Gra kończy się na żądanie użytkownika lub po przeprowadzeniu pionka na przeciwległą stronę planszy.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WYMIARY_X 5
#define WYMIARY_Y 5
void def_emp_table(char tablica[WYMIARY_X][WYMIARY_Y]){
    for(int x = 0;x < WYMIARY_X;x++){
        for(int y = 0;y < WYMIARY_Y;y++){
        tablica[x][y] = '.';     
        }
    }
}
void show_table(char tablica[WYMIARY_X][WYMIARY_Y],int p_x, int p_y){
    char character = 'P';
    for(int x = 0;x < WYMIARY_X;x++){
        for(int y = 0;y < WYMIARY_Y;y++){
        if(p_x == x && p_y == y){
            printf("%5c",character);
        }else{
            printf("%5c",tablica[x][y]);
        }
        
        }
        puts("\n");
    }
}

int main(){
    char tablica[WYMIARY_X][WYMIARY_Y];
    srand(time(NULL));
    int r = rand()%5;
    def_emp_table(tablica);
    show_table(tablica,0,r);
    
}