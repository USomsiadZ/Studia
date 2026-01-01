/*
Statek badawczy Orion One przemierza odległe sektory kosmosu, monitorując działanie swoich systemów. Każde zdarzenie, od rutynowych komunikatów po krytyczne alarmy, trafia do centralnego Systemu Logów Pokładowych.

Każdy wpis ma postać:

struct LogEntry {
    int id;                // identyfikator (nadawany automatycznie, narastająco)
    char message[64];      // treść komunikatu
    enum SystemType system;
    enum Severity severity;
    int timestamp;
    bool processed;        // czy log został już rozpatrzony
};

enum SystemType {
    SYSTEM_ENGINE,
    SYSTEM_LIFESUPPORT,
    SYSTEM_SENSORS,
    SYSTEM_NAVIGATION,
    SYSTEM_COMMS,
    SYSTEM_WEAPONS
};

enum Severity {
    SEV_INFO,
    SEV_WARNING,
    SEV_CRITICAL
};
Identyfikatory logów muszą być nadawane automatycznie - każdy kolejny wpis otrzymuje kolejny numer.

Twoim zadaniem jest zaimplementować działający fragment tego systemu: zarządzanie listą wpisów logów oraz wykonywanie podstawowych operacji analitycznych.

Dodawanie nowego wpisu logu
Odczytaj treść komunikatu, system źródłowy, poziom istotności i czas wystąpienia. Utwórz nowy wpis logu z automatycznym id i processed = false. Wstaw go na koniec listy.
Wyświetlanie wszystkich logów
Wyświetl wszystkie wpisy w czytelnej formie, tak aby oficer techniczny mógł przejrzeć historię zdarzeń na pokładzie.
Czyszczenie listy
Usuń wszystkie wpisy i zwolnij pamięć.
Oznaczanie logu jako przetworzonego
Oficer techniczny Orion One może oznaczyć wybrany wpis jako rozpatrzony. Zaimplementuj funkcję, która wyszukuje na liście log o podanym identyfikatorze id i jeśli taki log istnieje - ustawia jego pole processed na true.
Filtrowanie logów według poziomu istotności
Utwórz i zwróć nową listę, zawierającą tylko logi o wskazanym poziomie. Pozwala to oficerowi skupić się wyłącznie na interesujących go komunikatach.
Znalezienie najpoważniejszego logu
Znajdź i zwróć wpis o najwyższym poziomie istotności, a jeśli jest ich wiele - o największym czasie timestamp. Jeśli jest więcej niż jeden - zwróć pierwszy.
To funkcja, która pozwala szybko ustalić, który problem wymaga natychmiastowej reakcji.
Utworzenie listy logów nieprzetworzonych
Zgromadź wszystkie logi, które mają processed == false, w nowej liście.
Oficer operacyjny korzysta z takiej listy, aby wiedzieć, czym należy zająć się w pierwszej kolejności.
Wyszukiwanie logów zawierających dane słowo
Przeszukaj pole message.
Zwróć listę wpisów, które zawierają wskazany fragment tekstu (np. „error”, „temperature”, „engine”).
Pomaga to analizować przyczyny awarii.
Wyznaczenie systemu, który wygenerował najwięcej logów
Zwróć nazwę systemu, który wygenerował najwięcej logów ogółem. Dodatkowo przekaż, ile logów każdego typu wpisał na listę. 
Walidacja danych

Podczas tworzenia nowych wpisów logów należy zadbać o poprawność danych wejściowych.
System Orion One nie może przechowywać logów zawierających nieprawidłowe lub niespójne informacje.
*/
/*
1
2
3
4
5
6
7
8
9
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum SystemType {
    SYSTEM_ENGINE,
    SYSTEM_LIFESUPPORT,
    SYSTEM_SENSORS,
    SYSTEM_NAVIGATION,
    SYSTEM_COMMS,
    SYSTEM_WEAPONS
};

enum Severity {
    SEV_INFO,
    SEV_WARNING,
    SEV_CRITICAL
};

struct LogEntry {
    int id;                // identyfikator (nadawany automatycznie, narastająco)
    char message[64];      // treść komunikatu
    enum SystemType system;
    enum Severity severity;
    int timestamp;
    bool processed;        // czy log został już rozpatrzony
};


typedef struct Node{
    struct LogEntry log;
    struct Node *next;
}Node;

void new_log(Node **head, enum Severity severity, enum SystemType system, int timestamp, char message[64]){
    //brak obsługi pustej listy
    Node *n = calloc(1, sizeof(Node));
    if (n == NULL) {
        printf("Błąd alokacji pamięci");
        return;
    }
    int i = 0;
    Node *p = *head;
    while (p->next != NULL) {
        i++;
        p = p->next;
    }
    
    
    n->log.id = i + 1;
    n->log.processed = false;
    n->log.severity = severity;
    n->log.system = system;
    n->log.timestamp = timestamp;
    strcpy(n->log.message,message);
    n->next = NULL;
    
    

    p->next = n;

}








void show_menu(){
    printf("1)\n");
    printf("2)\n");
    printf("3)\n");
    printf("4)\n");
    printf("0)\n");
}
int option_menu(Node **head){
    int wybor;
    scanf("%d", &wybor);
    switch(wybor) {
        case 1:
            printf("Wybrano opcję 1\n");
            break;
        case 2:
            printf("Wybrano opcję 2\n");
            break;
        case 3:
            printf("Wybrano opcję 3\n");
            break;
        case 4:
            printf("Wybrano opcję 4\n");
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
    while(1){
        show_menu();
        if(option_menu(&head) == 0){
            break;
        }
        // kod
    }
    return 0;
}