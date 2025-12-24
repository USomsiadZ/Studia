/*
W Wielkiej Bibliotece przechowywane są bezcenne tomy magii, kroniki dawnych bitew i traktaty alchemiczne. Mistrz Bibliotekarz prowadzi rejestr wszystkich ksiąg znajdujących się w zbiorach.

Dana jest struktura opisująca pojedynczą księgę:


struct book {
    char author[32], title[64];
    int copies;
    float price;
};

Napisz zestaw funkcji zarządzających katalogiem bibliotecznym:

Funkcja pobierająca i zwracająca dane jednej księgi
Napisz funkcję, która wczytuje od użytkownika dane pojedynczej księgi przechowywanej w Wielkiej Bibliotece:
imię i nazwisko autora (np. "Aelindor Białe Pióro"),
tytuł księgi (np. "Kroniki Płonącego Smoka"),
liczbę egzemplarzy dostępnych w archiwum,
cenę jednego egzemplarza (w złotych koronach).
Funkcja powinna zwracać strukturę typu struct book.
Funkcja wypisująca dane księgi
Napisz funkcję, która wyświetla informacje o księdze w czytelnej formie, np.:
Author:                Aelindor Białe Pióro
Title:                 Kroniki Płonącego Smoka
No of copies:          12
Price:                 47.50 zk
Funkcja tworząca katalog zawierający część zbiorów Wielkiej Biblioteki
Napisz funkcję, która:
przyjmuje w parametrze liczbę ksiąg n,
tworzy tablicę o rozmiarze n,R
wypełnia ją danymi pobranymi od użytkownika (korzystając z funkcji z punktu 1),
zwraca całą tablicę.
Funkcja wyświetlająca zawartość tablicy
Napisz funkcję, która wyświetli wszystkie księgi z tablicy w kolejności ich występowania, każdą z osobna, w formacie znanym z punktu 2.
Funkcja obliczająca sumaryczną wartość zbiorów
Napisz funkcję, która obliczy łączną wartość wszystkich ksiąg w katalogu, zgodnie ze wzorem:
total_value = Σ (copies * price)
Wypisana wartość odpowiada temu, ile złotych koron wart jest fragment zbiorów przechowywany w bibliotece.
*/
#define SIZE 128
struct cadet
{
    char name[51];
    float note;
};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
int valid_name(char *name){
    int i = 0;
    while (name[i] != '\0')
    {
        if (!isalpha(name[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}
int name_name_check(char name1[51], char name2[51]){
    int i = 0;
    int correct = 1;
    while (name1[i] != '\0')
    {
        if (name1[i] != name2[i])
            correct = 0;
        i++;
    }
    return correct;
}
float name_srednia(struct cadet mark[SIZE], int index, char nname[51]){
    float sum = 0;
    int count = 0;
    for (int i = 0; i < index; i++)
    {
        if (name_name_check(mark[i].name, nname))
        {
            sum += mark[i].note;
            count++;
        }
    }
    return sum / (float)count;
}
void show_name(struct cadet mark[SIZE], char nname[51], int index)
{
    for (int i = 0; i < index; i++)
    {
        if (name_name_check(mark[i].name, nname))
        {
            printf("%.2f\n", mark[i].note);
        }
        else
        {
            printf("%s nie istnieje\n", nname);
            return;
        }
    }
    printf("Średnia: %f\n",name_srednia(mark,index,nname));
}
// niewiadomo czy potrzebne 
int count_names(struct cadet mark[SIZE], char nname[51],int index){
    int count = 0;
    for (int i = 0; i < index; i++)
    {
        if(name_name_check(mark[i].name,nname))count++;
    }
    return count;
}
//robi malloc z nazwami <=> to samo co polecenie uniq
void del_tab(struct cadet mark[SIZE],int index,int size){
    for (int i = index; i < size - 1; i++)
    {
        mark[i] = mark[i+1];
    }
}
int name_table(struct cadet mark[SIZE],int size,struct cadet name_tab[SIZE]){
    memcpy(name_tab,mark,size * sizeof(struct cadet));
    int result_size = size;
    for (int i = 0; i < result_size; i++)// Orginal przejście
    {
        for (int j = i+1; j < result_size; j++)// Orginal == subOrginal ? del_subOrginal : nic;
        {
            if(name_name_check(name_tab[i].name,name_tab[j].name)){
                del_tab(name_tab,j,result_size);
                result_size--;
                j--;
            }
        }
    }
    return result_size;
}
void numer_sort(struct cadet tab[SIZE],int size){
    struct cadet temp;
    for (int j = 0; j < size - 1; j++)
    {
        for (int i = 0; i < size - 1 - j; i++)
        {
            if (tab[i].note > tab[i + 1].note) {
                memcpy(&temp,&tab[i],sizeof(struct cadet));
                memcpy(&tab[i],&tab[i + 1],sizeof(struct cadet));
                memcpy(&tab[i + 1],&temp,sizeof(struct cadet));
            }
        }
    }
}
void sort(struct cadet tab[SIZE],int size,int start,int stop){
    struct cadet temp;
    int range_size = stop - start + 1;
    for (int j = 0; j < range_size - 1; j++)
    {
        for (int i = start; i < stop - j; i++)
        {
            if (strcmp(tab[i].name, tab[i + 1].name) > 0) {
                memcpy(&temp,&tab[i],sizeof(struct cadet));
                memcpy(&tab[i],&tab[i + 1],sizeof(struct cadet));
                memcpy(&tab[i + 1],&temp,sizeof(struct cadet));
            }
        }
    }
}
int do_raport(struct cadet mark[SIZE], int index,struct cadet raport[SIZE])
{
    int size_tab = name_table(mark,index,raport);
    for (int i = 0; i < size_tab; i++)
    {
        raport[i].note = name_srednia(mark, index, raport[i].name);
    }
    numer_sort(raport,size_tab);
    //Jeśli są dwie osoby z tą samą średnią to sortuje po nazwie
    int i = 0;
    while (i < size_tab)
    {
        int start = i;
        while (i < size_tab - 1 && raport[i].note == raport[i + 1].note)
        {
            i++;
        }
        int stop = i;
        if (stop > start)
        {
            sort(raport, size_tab, start, stop);
        }
        i++;
    }
    return size_tab;
}

int main()
{
    int raport_size = 0;
    struct cadet mark[SIZE];
    struct cadet raport[SIZE];
    int index = 0;
    int wybor = 0;
    char nname[51];
    while (1)
    {
        printf("Podaj wybor\n");
        printf("1: Dodaj ocene\n");
        printf("2: Wyświetl ocene kadeta\n");
        printf("3: Wyświetlenie raportu\n");
        wybor = 0;
        while (!(wybor > 0 && wybor <= 4))
        {
            scanf("%d", &wybor);
        }
        switch (wybor)
        {
        case 1:
            while (1)
            {
                printf("Podaj imie kadeta\n");
                scanf("%s", mark[index].name);
                if (valid_name(mark[index].name))
                    break;
            }
            while (1)
            {
                while (getchar() != '\n');
                printf("Podaj ocene kadeta\n");
                scanf("%f", &mark[index].note);
                if (mark[index].note >= 2 && mark[index].note <= 5)
                    break;
            }
            printf("Pomyślnie dodano : %s z oceną : %.2f\n", mark[index].name, mark[index].note);
            index++;
            break;
        case 2:
            printf("Podaj imie kadeta: ");
            scanf("%50s", nname);
            show_name(mark, nname, index);
            break;
        case 3:
            raport_size = do_raport(mark,index,raport);
            for (int i = 0; i < raport_size; i++)
            {
                printf("%s   :   %f\n",raport[i].name,raport[i].note);
            }
            break;
        default:
            break;
        }
    }
    printf("\n\n");
    return 0;
}