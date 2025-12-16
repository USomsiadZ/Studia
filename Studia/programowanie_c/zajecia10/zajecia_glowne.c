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
typedef struct Node {
    struct LogEntry entry;
    struct Node* next; // wskaźnik do kolejnego elementu
} Node;

Node* push_back(Node* head, struct LogEntry entry) {
    Node* n = calloc(1, sizeof(Node));
    n->entry = entry;
    n->next = NULL;

    if (head == NULL)
        return n;

    Node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = n;
    return head;
}
void dodanie_odczytu(Node** head, int* next_id) {
    char message[64];
    int system, poziom, czas;
    
    printf("Podaj treść komunikatu (max 63 znaki): ");
    scanf("%63s", message);
    
    printf("Podaj system źródłowy (0-5): ");
    scanf("%d", &system);
    
    printf("Podaj poziom istotności (0-2): ");
    scanf("%d", &poziom);
    
    printf("Podaj czas wystąpienia: ");
    scanf("%d", &czas);
    
    struct LogEntry entry;
    entry.id = *next_id;
    strcpy(entry.message, message);
    entry.system = system;
    entry.severity = poziom;
    entry.timestamp = czas;
    entry.processed = false;
    
    *head = push_back(*head, entry);
    (*next_id)++;
}
int main(){
    //Odczytaj treść komunikatu, system źródłowy, poziom istotności i czas wystąpienia. Utwórz nowy wpis logu z automatycznym id i processed = false. Wstaw go na koniec listy.
    Node *head = NULL;
    
    return 0;
}
