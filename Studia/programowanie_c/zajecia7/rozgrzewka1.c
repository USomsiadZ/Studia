/*
W komnacie znajduje się rząd kryształów energii, z których każdy emituje określony poziom mocy. Napisz program, który pozwoli użytkownikowi odczytywać i modyfikować energię wybranego kryształu - wyłącznie za pomocą wskaźników.
Wyświetl zawartość tablicy przy użyciu notacji wskaźnikowej.
Program ma uruchomić pętlę, która:
Pyta użytkownika, który kryształ chce wybrać (numer od 0 do 4). Wpisanie -1 kończy pętlę.
Po wybraniu numeru kryształu ustaw wskaźnik tak, by wskazywał na odpowiedni element tablicy (bez użycia indeksowania),
wypisz aktualny poziom energii poprzez dereferencję,
pozwól użytkownikowi wpisać nową wartość energii,
zapisz nową wartość przez wskaźnik.
Ponownie wyświetl zawartość tablicy.
W akademii magów badacze gromadzą kolekcje artefaktów, z których każdy ma swoją "moc energetyczną" wyrażoną jako liczba całkowita. Stwórz zestaw funkcji, które analizują i modyfikują tablice takich wartości.
Wszystkie operacje na tablicy mają być wykonane wyłącznie przez wskaźniki.
double average(const int *tab, int size);
Funkcja oblicza i zwraca średnią arytmetyczną wszystkich wartości.

int minValue(const int *tab, int size);
Zwraca najmniejszą wartość z tablicy.

int maxValue(const int *tab, int size);
Zwraca największą wartość z tablicy.

void swapValues(int *a, int *b);
Funkcja zamienia wartości w dwóch podanych miejscach tablicy. Zamiana odbywa się wyłącznie poprzez operacje na wskaźnikach, tzn. funkcja "widzi" tylko adresy zamienianych elementów - nie przekazujemy całej tablicy.

void printArray(const int *tab, int size);
Wyświetla zawartość tablicy na ekranie.

Magowie rozszerzyli swoje laboratorium i teraz przechowują zmienną liczbę artefaktów - dlatego tablica ich mocy musi być tworzona dynamicznie.
Napisz program, który:
tworzy tablicę dynamiczną o wielkości pobranej od użytkownika,
wypełnia ją wartościami podanymi przez użytkownika,
korzysta z funkcji napisanych w poprzednim zadaniu (average, minValue, maxValue, swapValues),
zwalnia pamięć po zakończeniu pracy.

Po ostatnich sukcesach Akademii Magów Laboratorium Artefaktów Mocy zostało oficjalnie wpisane do długoterminowego planu rozwoju. Rada Starszych przewiduje, że w przyszłości może powstać więcej laboratoriów, a każde będzie przechowywać własny zestaw artefaktów.
Zmodyfikuj wcześniejsze zadanie w taki sposób, by tworzenie, wypełnianie oraz zwalnianie tablicy odbywało się poprzez zdefiniowane funkcje. Dodaj również możliwość zmiany wielkości tablicy. Takie podejście umożliwi Radzie Starszym skalowanie infrastruktury Akademii wraz z rosnącą liczbą laboratoriów, co będzie niezbędne, gdy w kolejnych latach Akademia uruchomi nowe projekty badawcze.
*/
/*
1
2
*/
#include <stdio.h>
#include <stdlib.h>

void edit_crystal(int *tab,int *br){
    int input = 0;
    int *p = NULL;
    printf("\n");
    printf("Podaj nr kryształu: ");
    scanf("%d",&input);
    if(input == -1)*br = 1;
    p = (tab + input - 1);
    

        if(p != NULL){
            printf("%d\n",*p);
            printf("Podaj nowy poziom wskaźnika: ");
            scanf("%d",p);

        }

}
double average(const int *tab, int size){
    double suma = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        suma += *(tab + i);
    }
    return suma/i;
}
int minValue(const int *tab, int size){
    int m = *tab;
    for (int i = 0; i < size; i++)
    {
        m = (*(tab + i)) < m ? (*(tab + i)) : m;
    }
    return m;
}
int maxValue(const int *tab, int size){
    int m = *tab;
    for (int i = 0; i < size; i++)
    {
        m = (*(tab + i) > m) ? (*(tab + i)) : m;
    }
    return m;
}
void swapValues(int *a, int *b){
    int m = *b;
    *b = *a;
    *a = m;
}
void fill_value(int *tab,int size){
    for (int i = 0; i < size; i++)
    {
        *(tab + i) = (i + 1) + (i + 1) * 10;
    }
}
void printArray(const int *tab, int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d\n",*(tab + i));
    }
}
void show_menu(){
    printf("1) Edytuj\n");
    printf("2) Średnia\n");
    printf("3) Minimalna\n");
    printf("4) Maksymalna\n");
    printf("5) Zamiana\n");
    printf(" ");
    printf(" ");
}
void menu(int *tab,int size){
    int br = 0;
    int input = 0;
    int wartosc1,wartosc2;

    while(br == 0){
        printArray(tab,4);
        show_menu();
        scanf("%d",&input);
        switch (input)
        {
        case 1:
            edit_crystal(tab,&br);
            break;
        case 2:
            printf("%f\n",average(tab,size));
            break;
        case 3:
            printf("%d\n",minValue(tab,size));

            break;
        case 4:
            printf("%d\n",maxValue(tab,size));
            break;
        case 5:
            printf("Podaj nr 1: ");
            scanf("%d",&wartosc1);
            printf("Podaj nr 2: ");
            scanf("%d",&wartosc2);
            swapValues((tab + wartosc1 - 1),(tab + wartosc2 -1));
            break;
        case 6:

            break;
        }



    }
    
}

int main(){
    int size = 4;
    int *tab = malloc(size * sizeof(int));
    fill_value(tab,size);
    
    

    menu(tab,size);


}