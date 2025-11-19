/*
W grze planszowej gracz steruje jednym pionkiem, który musi dotrzeć z górnego do dolnego rzędu planszy, unikając przeszkód. Plansza ma wymiary 5×5 i przechowywana jest w postaci dwuwymiarowej tablicy znaków.
Napisz program, który utworzy tablicę i przygotuje rozgrywkę według poniższych zasad:
* Wszystkie pola planszy są początkowo puste (oznaczone znakiem '.'). {}
* W pierwszym wierszu (górnym) w losowej kolumnie umieszczony jest pionek gracza, oznaczony znakiem 'P'.{}
* W środkowych wierszach (od drugiego do czwartego) program losowo rozmieszcza kilka przeszkód oznaczonych znakiem '#'. Przeszkody nie mogą pojawić się w pierwszym ani w ostatnim wierszu ani na polach zajętych przez pionki.{}
* W ostatnim wierszu znajduje się strefa celu - miejsca, do których gracz ma doprowadzić pionek.{}

Następnie program umożliwia wykonywanie ruchów według poniższych zasad:
* Gracz podaje kierunek ruchu (W - w lewo, E - w prawo, N - w górę, S - w dół).{}
* Pionek może poruszyć się o jedno pole w wybranym kierunku, jeśli pole docelowe jest puste ('.') i znajduje się w granicach planszy.{}
* Jeśli na polu docelowym znajduje się przeszkoda ('#'), program powinien wyświetlić komunikat.{}
Program po każdym ruchu wyświetla stan planszy i pyta, czy gracz chce wykonać następny ruch. {}
Gra kończy się na żądanie użytkownika lub po przeprowadzeniu pionka na przeciwległą stronę planszy.{}
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WYMIARY_X 6
#define WYMIARY_Y 6
#define MAX_PRZESZKODY 2
void def_emp_table(char tablica[WYMIARY_X][WYMIARY_Y],char znak){
    for(int x = 0;x < WYMIARY_X;x++){
        for(int y = 0;y < WYMIARY_Y;y++){
        tablica[x][y] = znak;     
        }
    }
}
int zawiera(char table[][WYMIARY_Y],int x,int y){
    if(table[x][y] == '#'){
        return 1;
    }
    return 0;
}

void show_table(char tablica[WYMIARY_X][WYMIARY_Y],int p_x, int p_y,char przeszkody[WYMIARY_X][WYMIARY_Y],int m_x,int m_y){
    char character = 'P';
    char przeszkoda = '#';
    char miejsce = '@';
    for(int i = 0;i < 5; i++){
        printf("\n");
    }
    for(int y = 0;y < WYMIARY_Y;y++){
        for(int x = 0;x < WYMIARY_X;x++){
            if(p_x == x && p_y == y){
                printf("%5c",character);
            }else if('#' ==  przeszkody[x][y]){
                printf("%5c",przeszkoda);
            }else if(m_x == x && m_y == y){
                printf("%5c",miejsce);
            }
            else{
                printf("%5c",tablica[x][y]);
                
            }
        }
        puts("\n");
    }
}

int main(){
    char tablica[WYMIARY_X][WYMIARY_Y];
    char przeszkody[WYMIARY_X][WYMIARY_Y];
    int x,y,postac_x,miejsce_x;
    int postac_y = 0;
    char znak;
    int win = 0;

    srand(time(NULL));
    def_emp_table(przeszkody,'0');
    for(int i = 0;i < MAX_PRZESZKODY;i++){
        x = rand()%3 + 1;
        y = rand()%3 + 1;
        przeszkody[x][y] = '#';
    }
        
    postac_x = rand()%5;
    miejsce_x = rand()%5;
    def_emp_table(tablica,'.');
    show_table(tablica,postac_x,postac_y,przeszkody,miejsce_x,WYMIARY_Y - 1);

    while(win != 1){
        scanf("%c",&znak);
        if(znak=='w' && postac_y > 0 && !zawiera(przeszkody,postac_x,postac_y - 1)){
            postac_y -= 1;
        }
        if(znak=='a' && postac_x  > 0 && !zawiera(przeszkody,postac_x - 1,postac_y)){
            postac_x -= 1;
        }
        if(znak=='d' && postac_x + 1< WYMIARY_X  && !zawiera(przeszkody,postac_x + 1,postac_y)){
            postac_x += 1;
        }
        if(znak=='s' && postac_y + 1< WYMIARY_Y  && !zawiera(przeszkody,postac_x,postac_y + 1)){
            postac_y += 1;
        }
        if(miejsce_x == postac_x && WYMIARY_Y - 1 == postac_y){
            win = 1;
        }
        show_table(tablica,postac_x,postac_y,przeszkody,miejsce_x,WYMIARY_Y - 1);
    }
    
}