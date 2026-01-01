/*
Statek kosmiczny Orion One otrzymuje od Centrali Nawigacyjnej pliki tekstowe zawierające listę galaktycznych współrzędnych punktów, które mogą wymagać odwiedzenia. W pliku znajdują się wartości rzeczywiste zapisane w dowolnej liczbie wierszy, oddzielone białymi znakami. Kolejne dwie liczby tworzą jedną parę współrzędnych galaktycznych: długość oraz szerokość. Ponieważ dane pochodzą z wielu stacji obserwacyjnych i mogą nie mieć idealnej struktury, program powinien najpierw sprawdzić, czy plik jest poprawny, to znaczy, czy zawiera wyłącznie liczby rzeczywiste oraz czy ich liczba jest parzysta, tak aby można było poprawnie utworzyć wszystkie pary współrzędnych.

Jeśli plik przejdzie weryfikację, program wczytuje wszystkie współrzędne do dynamicznej tablicy i wyświetla je użytkownikowi. Kapitan statku podaje następnie bieżącą pozycję Oriona One oraz promień działania pokładowego radaru. Program oblicza odległość każdego punktu od pozycji statku i usuwa z listy te miejsca, które znajdują się poza zasięgiem radaru, pozostawiając jedynie te, które statek może realnie odwiedzić.

Po przefiltrowaniu danych program zapisuje pozostałe współrzędne do pliku binarnego w formacie nieczytelnym dla człowieka.

Celem zadania jest napisanie programu, który przeprowadza cały powyższy proces. Program powinien prawidłowo zarządzać pamięcią dynamiczną i być odporny na błędne dane wejściowe. Na potrzeby realizacji zadania można wykorzystać własną strukturę, reprezentującą pojedynczy punkt galaktyczny.
*/
/*
1. Stworzyć strukturę reprezentującą punkt galaktyczny (długość, szerokość){}
2. Zaimplementować funkcję weryfikującą plik wejściowy:
   - Sprawdzić czy plik zawiera wyłącznie liczby rzeczywiste{}
   - Sprawdzić czy liczba wartości jest parzysta (aby utworzyć pary współrzędnych){}
   - Zwrócić informację o poprawności pliku{}
3. Wczytać wszystkie współrzędne z pliku do dynamicznie alokowanej tablicy struktur{}
4. Wyświetlić wszystkie wczytane współrzędne użytkownikowi{}
5. Pobrać od użytkownika:
   - Bieżącą pozycję statku (długość, szerokość){}
   - Promień działania radaru{}
6. Obliczyć odległość każdego punktu od pozycji statku (wzór euklidesowy){}
7. Usunąć z tablicy wszystkie punkty, których odległość przekracza promień radaru{}
8. Zaktualizować rozmiar tablicy po usunięciu punktów{}
9. Zapisć pozostałe współrzędne do pliku binarnego (format binarny){}
10. Zwolnić zaalokowaną pamięć dynamiczną{}
*/
// Plik: 11 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct{
    int x;
    int y;
}galax;
// 0 - no error
int is_valid(){
    FILE *file = fopen("glowne.txt", "r");
    char tmp;
    int result;
    while ((result = fscanf(file, "%c", &tmp)) == 1) {
        if(!(tmp >= '0' && tmp <= '9') && !isspace(tmp)){
            
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
int count(){
    FILE *file = fopen("glowne.txt", "r");
    if(!file)return -1;
    int i = 0;
    int value_load = 0;
    int tmp_x,tmp_y;
    while (1) {
        value_load = fscanf(file,"%d %d",&tmp_x,&tmp_y);
        if(value_load == 1){
            return 1;
        }else if (value_load == EOF) {
            break;
        }
        i++;
    }
    return i;
}
void file_load(galax *tab,int size){
    FILE *file = fopen("glowne.txt", "r");
    for (int i = 0; i < size; i++)
    {
        fscanf(file,"%d %d",&tab[i].x,&tab[i].y);
    }
        

    fclose(file);
}
void show_tab(galax *tab,int size){
    printf(" x   :    y\n");
    for (int i = 0; i < size; i++)
    {
        printf("%2d   :   %2d\n",tab[i].x,tab[i].y);
    }
}
int distanse(int x1,int y1,int x2,int y2){
    int x = abs(x1- x2);
    int y = abs(y1 -y2);
    int r = (int)sqrt(x*x + y*y);

    return r;
}
void del_tab(galax *tab,int *size,int id){
    for (int i = id; i < *size - 1; i++)
    {
        tab[i] = tab[i+1];
    }
    (*size)--;
}
void del_under_distanse(galax *tab,int *size,int r,int x,int y){
    for (int i = 0; i < *size; i++)
    {
        if(distanse(x, y, tab[i].x, tab[i].y) > r){del_tab(tab,size, i); i--;};
    }
}
void save_to_bin(galax *tab,int size){
    FILE *file = fopen("wynik.bin", "wb");
    if(!file) return;
    fwrite(tab,sizeof(galax),size, file);
    fclose(file);
}
int main(){
    int x = 0;
    int y = 0;
    int r = 0;
    int size = count();
    if(size == -1){
        printf("Błąd wczytania pliku");
        return 1;
    }
    galax *tab = malloc(size * sizeof(galax));
    file_load(tab,size);
    int valid = is_valid();
    if(valid == 1){
        printf("Błąd wczytania pliku");
        return 1;
    }
    show_tab(tab, size);
    printf("Podaj x i y statku aby uzyskac pomiar z okolicy");
    scanf("%d %d",&x,&y);
    printf("Podaj zasiek dzialania radaru");
    scanf("%d",&r);
    del_under_distanse(tab,&size,r,x,y);
    show_tab(tab, size);
    save_to_bin(tab,size);


    return 0;
}