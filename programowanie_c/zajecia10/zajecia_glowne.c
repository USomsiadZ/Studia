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
    int id;
    char message[64];
    enum SystemType system;
    enum Severity severity;
    int timestamp;
    bool processed;
};


typedef struct Node{
    struct LogEntry log;
    struct Node *next;
}Node;

void new_log(Node **head, enum Severity severity, enum SystemType system, int timestamp, char message[64]){
    Node *n = calloc(1, sizeof(Node));
    if (n == NULL) {
        printf("Błąd alokacji pamięci");
        return;
    }

    n->log.processed = false;
    n->log.severity = severity;
    n->log.system = system;
    n->log.timestamp = timestamp;
    strcpy(n->log.message,message);
    n->next = NULL;
    if(*head == NULL){
        n->log.id = 1;
        *head = n;
    }else{
        int i = 1;
        Node *p = *head;
        while (p->next != NULL) {
            i++;
            p = p->next;
        }
        n->log.id = i + 1;
        p->next = n;
    }
    

}
void print_logs(Node *head){
    Node *p = head;
    while(p != NULL){
        printf("========================================\n");
        printf(" ID:           %d\n", p->log.id);
        printf(" Message:      %s\n", p->log.message);
        printf(" Processed:    %s\n", p->log.processed ? "Yes" : "No");
        
        printf(" Severity:     ");
        switch(p->log.severity){
            case SEV_INFO: printf("INFO\n"); break;
            case SEV_WARNING: printf("WARNING\n"); break;
            case SEV_CRITICAL: printf("CRITICAL\n"); break;
            default: printf("UNKNOWN\n"); break;
        }
        
        printf(" System:       ");
        switch(p->log.system){
            case SYSTEM_ENGINE: printf("ENGINE\n"); break;
            case SYSTEM_LIFESUPPORT: printf("LIFESUPPORT\n"); break;
            case SYSTEM_SENSORS: printf("SENSORS\n"); break;
            case SYSTEM_NAVIGATION: printf("NAVIGATION\n"); break;
            case SYSTEM_COMMS: printf("COMMS\n"); break;
            case SYSTEM_WEAPONS: printf("WEAPONS\n"); break;
            default: printf("UNKNOWN\n"); break;
        }
        
        printf(" Timestamp:    %d\n", p->log.timestamp);
        printf("========================================\n\n");
        p = p->next;
    }
}
void delete_logs(Node **head){
    Node *p = *head;
    Node *next;
    while (p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
}
void processed_log(Node **head, int id){
    if (*head == NULL) {
        printf("Head jest NULL");
        return;
    }
    Node *p = *head;
    
    while (p != NULL) {
        if(p->log.id == id){
            p->log.processed = true;
            return;
        }
        p = p->next;
    }
}

void add_log_to_list(Node **head, struct LogEntry *log){
    Node *n = calloc(1, sizeof(Node));
    if(n == NULL){
        printf("Brak pamięci");
        return;
    }

    n->log.id = log->id;
    n->log.processed = log->processed;
    n->log.severity = log->severity;
    n->log.system = log->system;
    n->log.timestamp = log->timestamp;
    strcpy(n->log.message, log->message);
    n->next = NULL;

    if(*head == NULL){
        *head = n;
    }else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = n;
    }
}

void filter_logs(Node *head, enum Severity severity, Node **hydrahead){
    if (head == NULL) {
        printf("Head NULL");
        return;
    }
    Node *p = head;

    while (p != NULL) {
        if (p->log.severity == severity) {
            add_log_to_list(hydrahead, &(p->log));
        }
        p = p->next;
    }
}
Node *find_node_by_id(Node *head, int id){
    Node *p = head;
    while (p != NULL) {
        if (p->log.id == id) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int find_timespand(Node *head,int id){
    Node *node = find_node_by_id(head, id);
    if (node != NULL) {
        return node->log.timestamp;
    }
    return -1;
}

struct Node *find_most_severe_log(Node *head){
    Node *p = head;
    int *tab = malloc(10 * sizeof(int));
    int count = 0;
    while (p != NULL) {
        if(p->log.severity == SEV_CRITICAL){
            if (count > 0 && count % 10 == 0) {
                int *j = realloc(tab, sizeof(int) * (count + 10));
                if(j){
                    tab = j;
                }else {
                    printf("Brak miejsca ram");
                    free(tab);
                    return NULL;
                }
            }
            *(tab + count) = p->log.id;
            count++;
        }
        p = p->next;
    }
    if(count == 0){
        free(tab);
        return NULL;
    }
    if(count == 1){
        Node *result = find_node_by_id(head, *tab);
        free(tab);
        return result;
    }
    int max_timestamp = find_timespand(head, *tab);
    int max_id = *tab;
    for (int i = 1; i < count; i++)
    {
        int value = find_timespand(head, *(tab + i));
        if(max_timestamp < value){
            max_timestamp = value;
            max_id = *(tab + i);
        }
    }
    Node *result = find_node_by_id(head, max_id);
    free(tab);
    return result;
}

void get_unprocessed_logs(Node *head, Node **unprocessed_head){
    if (head == NULL) {
        return;
    }
    Node *p = head;
    
    while (p != NULL) {
        if (p->log.processed == false) {
            add_log_to_list(unprocessed_head, &(p->log));
        }
        p = p->next;
    }
}
void word_search(Node *head,char word[64]){
    Node *p = head;
    while (p != NULL) {
        if (strstr(p->log.message, word) != NULL) {
            printf("========================================\n");
            printf(" ID:           %d\n", p->log.id);
            printf(" Message:      %s\n", p->log.message);
            printf(" Processed:    %s\n", p->log.processed ? "Yes" : "No");
            
            printf(" Severity:     ");
            switch(p->log.severity){
                case SEV_INFO: printf("INFO\n"); break;
                case SEV_WARNING: printf("WARNING\n"); break;
                case SEV_CRITICAL: printf("CRITICAL\n"); break;
                default: printf("UNKNOWN\n"); break;
            }
            
            printf(" System:       ");
            switch(p->log.system){
                case SYSTEM_ENGINE: printf("ENGINE\n"); break;
                case SYSTEM_LIFESUPPORT: printf("LIFESUPPORT\n"); break;
                case SYSTEM_SENSORS: printf("SENSORS\n"); break;
                case SYSTEM_NAVIGATION: printf("NAVIGATION\n"); break;
                case SYSTEM_COMMS: printf("COMMS\n"); break;
                case SYSTEM_WEAPONS: printf("WEAPONS\n"); break;
                default: printf("UNKNOWN\n"); break;
            }
            
            printf(" Timestamp:    %d\n", p->log.timestamp);
            printf("========================================\n\n");
        }
        p = p->next;
    }
}

void find_most_logs_system(Node *head){
    if (head == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }
    
    int counts[6] = {0};
    Node *p = head;
    
    while (p != NULL) {
        counts[p->log.system]++;
        p = p->next;
    }
    
    int max_count = counts[0];
    int max_system = 0;
    for (int i = 1; i < 6; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_system = i;
        }
    }
    
    printf("\n=== Statystyki systemów ===\n");
    printf("ENGINE:       %d logów\n", counts[SYSTEM_ENGINE]);
    printf("LIFESUPPORT:  %d logów\n", counts[SYSTEM_LIFESUPPORT]);
    printf("SENSORS:      %d logów\n", counts[SYSTEM_SENSORS]);
    printf("NAVIGATION:   %d logów\n", counts[SYSTEM_NAVIGATION]);
    printf("COMMS:        %d logów\n", counts[SYSTEM_COMMS]);
    printf("WEAPONS:      %d logów\n", counts[SYSTEM_WEAPONS]);
    
    printf("\n=== System z największą liczbą logów ===\n");
    switch(max_system){
        case SYSTEM_ENGINE: printf("ENGINE - %d logów\n", max_count); break;
        case SYSTEM_LIFESUPPORT: printf("LIFESUPPORT - %d logów\n", max_count); break;
        case SYSTEM_SENSORS: printf("SENSORS - %d logów\n", max_count); break;
        case SYSTEM_NAVIGATION: printf("NAVIGATION - %d logów\n", max_count); break;
        case SYSTEM_COMMS: printf("COMMS - %d logów\n", max_count); break;
        case SYSTEM_WEAPONS: printf("WEAPONS - %d logów\n", max_count); break;
    }
    printf("\n");
}

void show_menu(){
    printf("\n=== System Logów Pokładowych Orion One ===\n");
    printf("1. Dodaj nowy wpis logu\n");
    printf("2. Wyświetl wszystkie logi\n");
    printf("3. Wyczyść listę logów\n");
    printf("4. Oznacz log jako przetworzony\n");
    printf("5. Filtruj logi według poziomu istotności\n");
    printf("6. Znajdź najpoważniejszy log\n");
    printf("7. Pokaż nieprzetworzone logi\n");
    printf("8. Wyszukaj logi zawierające słowo\n");
    printf("9. Wyznacz system z największą liczbą logów\n");
    printf("0. Wyjście\n");
    printf("Wybierz opcję: ");
}
int option_menu(Node **head){
    int wybor;
    scanf("%d", &wybor);
    switch(wybor) {
        case 1: {
            char message[64];
            int severity, system, timestamp;
            printf("Podaj treść komunikatu: ");
            getchar();
            fgets(message, 64, stdin);
            message[strcspn(message, "\n")] = 0;
            
            printf("Podaj poziom istotności (0=INFO, 1=WARNING, 2=CRITICAL): ");
            scanf("%d", &severity);
            
            printf("Podaj system (0=ENGINE, 1=LIFESUPPORT, 2=SENSORS, 3=NAVIGATION, 4=COMMS, 5=WEAPONS): ");
            scanf("%d", &system);
            
            printf("Podaj timestamp: ");
            scanf("%d", &timestamp);
            
            new_log(head, severity, system, timestamp, message);
            printf("Log dodany pomyślnie.\n");
            break;
        }
        case 2:
            print_logs(*head);
            break;
        case 3:
            delete_logs(head);
            printf("Lista logów wyczyszczona.\n");
            break;
        case 4: {
            int id;
            printf("Podaj ID logu do oznaczenia jako przetworzony: ");
            scanf("%d", &id);
            processed_log(head, id);
            printf("Log oznaczony jako przetworzony.\n");
            break;
        }
        case 5: {
            int severity;
            printf("Podaj poziom istotności (0=INFO, 1=WARNING, 2=CRITICAL): ");
            scanf("%d", &severity);
            Node *filtered = NULL;
            filter_logs(*head, severity, &filtered);
            printf("\n=== Filtrowane logi ===\n");
            print_logs(filtered);
            delete_logs(&filtered);
            break;
        }
        case 6: {
            Node *most_severe = find_most_severe_log(*head);
            if (most_severe != NULL) {
                printf("\n=== Najpoważniejszy log ===\n");
                printf("========================================\n");
                printf(" ID:           %d\n", most_severe->log.id);
                printf(" Message:      %s\n", most_severe->log.message);
                printf(" Processed:    %s\n", most_severe->log.processed ? "Yes" : "No");
                
                printf(" Severity:     ");
                switch(most_severe->log.severity){
                    case SEV_INFO: printf("INFO\n"); break;
                    case SEV_WARNING: printf("WARNING\n"); break;
                    case SEV_CRITICAL: printf("CRITICAL\n"); break;
                    default: printf("UNKNOWN\n"); break;
                }
                
                printf(" System:       ");
                switch(most_severe->log.system){
                    case SYSTEM_ENGINE: printf("ENGINE\n"); break;
                    case SYSTEM_LIFESUPPORT: printf("LIFESUPPORT\n"); break;
                    case SYSTEM_SENSORS: printf("SENSORS\n"); break;
                    case SYSTEM_NAVIGATION: printf("NAVIGATION\n"); break;
                    case SYSTEM_COMMS: printf("COMMS\n"); break;
                    case SYSTEM_WEAPONS: printf("WEAPONS\n"); break;
                    default: printf("UNKNOWN\n"); break;
                }
                
                printf(" Timestamp:    %d\n", most_severe->log.timestamp);
                printf("========================================\n\n");
            } else {
                printf("Nie znaleziono logu.\n");
            }
            break;
        }
        case 7: {
            Node *unprocessed = NULL;
            get_unprocessed_logs(*head, &unprocessed);
            printf("\n=== Nieprzetworzone logi ===\n");
            print_logs(unprocessed);
            delete_logs(&unprocessed);
            break;
        }
        case 8: {
            char word[64];
            printf("Podaj słowo do wyszukania: ");
            getchar();
            fgets(word, 64, stdin);
            word[strcspn(word, "\n")] = 0;
            printf("\n=== Logi zawierające '%s' ===\n", word);
            word_search(*head, word);
            break;
        }
        case 9:
            find_most_logs_system(*head);
            break;
        case 0:
            printf("Wyjście z programu.\n");
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
    }
    delete_logs(&head);
    return 0;
}