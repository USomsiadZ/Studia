/*
Podczas ekspedycji do magicznej dżungli Ruun’Kara adepci zapisują znalezione artefakty w Zwoju Odkryć, przchowywanego w liście jednokierunkowej.
Każdy element listy zawiera:

moc artefaktu (liczba całkowita),
nazwę artefaktu (łańcuch znaków).
Zaimplementuj następujące funkcjonalności (postaci kolejnych funkcji programu):

Tworzenie Zwoju
Napisz funkcję tworzącą listę zawierającą n losowych artefaktów.
Artefakty wstawiane są na początek listy.
(Nazwy mogą być wybierane z krótkiej tablicy losowych nazw:
const char* artifacts[] = {
    "Talizman Zgubionego Wczoraj",
    "Mlotek Do Glaskania",
    "Krysztal Wiecznej Zdjeciowki",
    "Gwizdek Na Komary W Krawatach",
    "Klejnot Huncwota",
    "Kapelusz Na Lewa Strone",
    "Pierscien Wiecznie Spozniony",
    "Kamien Krzyczacy Po Cichu",
    "Amulet Dwoch Lewych Skarpet",
    "Lampa ByleCzego"
};
)
Wyświetlanie Zwoju
Wypisz nazwy i moce wszystkich artefaktów.
Wyszukiwanie artefaktu po nazwie
Sprawdź, czy w liście znajduje się artefakt o podanej nazwie.
Zwróć true/false.
Pozycja pierwszego artefaktu o danej nazwie
Zwróć numer pierwszego wystąpienia w liście lub 0, jeśli brak.
Zliczanie wystąpień artefaktów o danej nazwie.
Sprawdź, ile razy dany artefakt znajduje się w Zwoju.
Zwróć te wartość lub 0, jeżeli nie występuje.
Oczyszczenie Zwoju
Zwalnianie pamięci i usuwanie całej listy.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

const char* artifacts[] = {
    "Talizman Zgubionego Wczoraj",
    "Mlotek Do Glaskania",
    "Krysztal Wiecznej Zdjeciowki",
    "Gwizdek Na Komary W Krawatach",
    "Klejnot Huncwota",
    "Kapelusz Na Lewa Strone",
    "Pierscien Wiecznie Spozniony",
    "Kamien Krzyczacy Po Cichu",
    "Amulet Dwoch Lewych Skarpet",
    "Lampa ByleCzego"
};

typedef struct Node{
    int moc;
    char nazwa[128];
    struct Node* next;
}Node;

Node *new_roll(Node *head){
    int size = rand()%10 + 1;
    for (int i = 0; i < size; i++)
    {
        Node *n = calloc(1, sizeof(Node));
        
        strcpy(n->nazwa, artifacts[rand()%9]);
        n->moc = rand()%100 + 1;

        n->next = head;
        head = n;
    }
    return head;
}
void print_roll(Node *head){
    Node *n = head;
    while (n != NULL) {
        printf("%s : %d \n",n->nazwa, n->moc);
        n = n->next;
    }
}
int exist(Node *head,char nazwa[128]){
    Node *n = head;
    while (n != NULL) {
        if(strcmp(n->nazwa, nazwa) == 0)return 1;
        n = n->next;
    }
    return 0;
}
int position(Node *head,char nazwa[128]){
    Node *n = head;
    int i = 0;
    while (n != NULL) {
        if(strcmp(n->nazwa, nazwa) == 0){
            return i;
        }
        n = n->next;
        i++;
    }
    return -1;
}
int count_roll(Node *head,char nazwa[128]){
    Node *p = head;
    int count = 0;
    while (p != NULL) {
        if (strcmp(p->nazwa,nazwa) == 0) {
            count++;
        }
        p = p->next;
    }
    return count;
}
void delete_roll(Node **head){
    Node *p = *head;
    Node *next;
    while (p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
}
void show_menu(){
    printf("1)Wypełnij zwoj\n");
    printf("2)Print zwoj\n");
    printf("3)Czy wystepuje\n");
    printf("4)Pozycja\n");
    printf("5)Zlicz wystąpienia\n");
    printf("0)\n");
}
int option_menu(Node **head){
    int wybor;
    char rob[128];
    int rb = 0;
    scanf("%d", &wybor);
    switch(wybor) {
        case 1:
            printf("Wybrano opcję 1\n");
            *head = new_roll(*head);
            break;
        case 2:
            printf("Wybrano opcję 2\n");
            print_roll(*head);
            break;
        case 3:
            printf("Wybrano opcję 3\n");
            while(getchar() != '\n');
            scanf("%[^\n]",rob);
            rb = exist(*head, rob);
            if(rb){printf("Istnieje\n");}else{printf("Nie instnieje\n");}
            break;
        case 4:
            printf("Wybrano opcję 4\n");
            while(getchar() != '\n');
            scanf("%[^\n]",rob);
            rb = position(*head,rob);
            if (rb == -1) {
                printf("Nie znaleziono");
            }else{
                printf("Index elementu %d\n",rb);
            }
            break;
         case 5:
            printf("Wybrano opcję 5\n");
            while(getchar() != '\n');
            scanf("%[^\n]",rob);
            rb = count_roll(*head, rob);
            if (rb == 0) {
            printf("Nie znaleziono wystąpienia\n");
            } else{
                printf("Znaleziono %d wystąpień\n",rb);
            }
            break;
         case 6:
            printf("Wybrano opcję 6\n");
            delete_roll(head);
            break;
        
        case 0:
            printf("Wyjście z programu\n");
            return 0;
        default:
            printf("Nieznana opcja\n");
            break;
    }
    return 1;
}
int main(){
    Node *head = NULL;
    

    srand(time(NULL));
    while(1){
        show_menu();
        if(option_menu(&head) == 0){
            break;
        }
        // kod
    }
    return 0;
}
