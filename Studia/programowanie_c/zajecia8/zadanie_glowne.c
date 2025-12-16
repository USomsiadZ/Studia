/*
Dziennik Akademii Załogi – Statek Kosmiczny Orion One

Na pokładzie statku badawczego Orion One działa Akademia Załogi, odpowiedzialna za szkolenie pilotów, techników i oficerów naukowych. Kadra instruktorska prowadzi rejestr ocen z misji treningowych i testów symulacyjnych.

Dane pojedynczego kadeta przechowywane są w strukturze:


struct cadet {
    char name[51];
    float note;
};

Napisz program wspierający Dziennik Akademii Załogi Orion One, realizujący poniższe funkcje:

Rejestrowanie nowej oceny kadeta
Po podaniu nazwiska kadeta oficer prowadzący może wystawić mu ocenę za wykonaną symulację lub zadanie pokładowe.
Oceny zapisywane są w pojedynczej tablicy wpisów treningowych, w której każda ocena jest osobnym rekordem (nawet jeśli dotyczy tego samego kadeta).
Tablica powinna być przygotowana z odpowiednim zapasem miejsca; dodatkowa zmienna przechowuje liczbę aktualnie wykorzystanych pozycji.
Nazwisko kadeta musi składać się wyłącznie z liter.
Dozwolone wartości ocen to: 2, 3, 3.5, 4, 4.5, 5 - jeśli oficer wprowadzi inną wartość, system powinien poprosić o ponowne podanie danych (aż do skutku).
Wyświetlanie historii ocen wybranego kadeta
Po podaniu nazwiska system powinien:
wyświetlić wszystkie oceny, jakie dany kadet uzyskał podczas szkoleń,
obliczyć i wyświetlić jego średnią ocenę,
poinformować, jeśli kadet nie figuruje w rejestrze lub nie ma żadnych wpisów.
Generowanie końcowego raportu Akademii Załogi
System powinien utworzyć raport podsumowujący wyniki szkolenia załogi:
Raport to nowa tablica rekordów typu struct cadet,
Każdy kadet powinien pojawić się w raporcie tylko raz,
Ocena końcowa kadeta to średnia jego wszystkich ocen z głównej tablicy, zaokrąglona i zweryfikowana wg tych samych zasad poprawności co dane wejściowe,
Raport należy posortować według oceny końcowej (malejąco lub rosnąco - wg Twojego wyboru, ale konsekwentnie),
Jeśli kilku kadetów ma taką samą ocenę - sortować dalej alfabetycznie po nazwisku.
Walidacja danych

W całym programie obowiązują następujące zasady:

Nazwisko może zawierać jedynie litery (bez cyfr i znaków specjalnych).
Ocena musi należeć do zbioru: {2, 3, 3.5, 4, 4.5, 5}.
W przypadku błędnych danych należy ponawiać wczytywanie aż do uzyskania poprawnych wartości.
Można i warto stworzyć funkcje pomocnicze realizujące bezpieczne pobieranie nazwiska i oceny.
*/

//Nazwisko kadeta musi składać się wyłącznie z liter. 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct cadet {
    char name[51];
    float note;
};
int valid_name(char name[51],int count){
    for (int i = 0; i < 51; i++)
    {
        //tutaj skończyłem
    }
}
void nowy_kadet(struct cadet cadet[128],int *nr){
    printf("Podaj nazwisko");
    printf("Podaj Ocena");
    scanf("%50s",&cadet[*nr].name);
    scanf("%f",&cadet[*nr].note);
    (*nr)++;

};
int main(){
    struct cadet cadets[128];
    int count = 0;

    return 0;
}