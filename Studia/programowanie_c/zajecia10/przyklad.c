#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int major;   // część główna daty, np. 7683
    int minor;   // część ułamkowa, np. 4 oznacza 0.4
} Stardate;

typedef struct Node {
    Stardate date;     // czas pomiaru
    double rad;        // poziom promieniowania
    struct Node* next; // wskaźnik do kolejnego elementu
} Node;

void print_stardate(Stardate s);
bool stardate_less_equal(Stardate a, Stardate b);

Node* push_back(Node* head, Stardate date, double rad);
Node* push_front(Node* head, Stardate date, double rad);
Node* free_list(Node* head);
void print_list(Node* head);
int count_elements(Node* head);
bool average(Node* head, double* result);
bool find_min(Node* head, double* result);
bool find_max(Node* head, double* result);
int count_range(Node* head, Stardate from, Stardate to);
Node* filter_by_radiation(Node* head, double threshold);

int main(void) {
    Node* head = NULL;

    head = push_back(head, (Stardate){7683, 1}, 12.5);
    head = push_back(head, (Stardate){7683, 3}, 18.2);
    head = push_back(head, (Stardate){7683, 4}, 25.7);
    head = push_back(head, (Stardate){7683, 8}, 9.1);
    head = push_back(head, (Stardate){7684, 2}, 30.4);

    printf("=== Wszystkie pomiary ===\n");
    print_list(head);

    printf("\nLiczba pomiarów: %d\n", count_elements(head));

    double avg;
    if (average(head, &avg)) {
        printf("Średnia promieniowania: %.2f\n", avg);
    } else {
        printf("Brak danych do obliczenia średniej.\n");
    }

    double min, max;
    if (find_min(head, &min)) printf("Minimalne promieniowanie: %.2f\n", min);
    if (find_max(head, &max)) printf("Maksymalne promieniowanie: %.2f\n", max);

    Stardate from = {7683, 2};
    Stardate to   = {7683, 8};
    int in_range = count_range(head, from, to);
    printf("\nPomiary w zakresie 7683.2 - 7683.8: %d\n", in_range);

    printf("\n=== Pomiary powyżej 20.0 ===\n");
    Node* strong = filter_by_radiation(head, 20.0);
    print_list(strong);

    head = free_list(head);
    strong = free_list(strong);

    return 0;
}


void print_stardate(Stardate s) {
    printf("%d.%d", s.major, s.minor);
}
bool stardate_less_equal(Stardate a, Stardate b) {
    if (a.major < b.major) return true;
    if (a.major > b.major) return false;
    return a.minor <= b.minor;
}
Node* push_back(Node* head, Stardate date, double rad) {
    Node* n = calloc(1, sizeof(Node));
    n->date = date;
    n->rad = rad;

    if (head == NULL)
        return n;  

    Node* p = head;
    while (p->next != NULL) {
        p = p->next;   
    }
    p->next = n;
    return head;
}
Node* push_front(Node* head, Stardate date, double rad) {
    Node* n = calloc(1, sizeof(Node));
    n->date = date;
    n->rad = rad;
    n->next = head;
    return n;   
}
Node* free_list(Node* head) {
    Node* p = head;
    while (p != NULL) {
        Node* next = p->next;  
        free(p);               
        p = next;              
    }
    return NULL;               
}
void print_list(Node* head) {
    Node* p = head;
    while (p != NULL) {
        print_stardate(p->date);
        printf(" — Radiation: %.2f\n", p->rad);
        p = p->next;
    }
}
int count_elements(Node* head) {
    int count = 0;
    for (Node* p = head; p != NULL; p = p->next) {
        count++;
    }
    return count;
}
bool average(Node* head, double* result) {
    int count = 0;
    double sum = 0;

    for (Node* p = head; p != NULL; p = p->next) {
        sum += p->rad;
        count++;
    }

    if (count == 0)
        return false;            

    *result = sum / count;
    return true;
}
bool find_min(Node* head, double* result) {
    if (head == NULL) return false;

    double min = head->rad;
    for (Node* p = head->next; p != NULL; p = p->next) {
        if (p->rad < min) min = p->rad;
    }

    *result = min;
    return true;
}
bool find_max(Node* head, double* result) {
    if (head == NULL) return false;

    double max = head->rad;
    for (Node* p = head->next; p != NULL; p = p->next) {
        if (p->rad > max) max = p->rad;
    }

    *result = max;
    return true;
}
int count_range(Node* head, Stardate from, Stardate to) {
    int result = 0;

    bool count_all = (from.major == -1 && to.major == -1);

    for (Node* p = head; p != NULL; p = p->next) {
        if (count_all ||
            (stardate_less_equal(from, p->date) &&
             stardate_less_equal(p->date, to)))
        {
            result++;
        }
    }

    return result;
}
Node* filter_by_radiation(Node* head, double threshold) {
    Node* result = NULL;

    for (Node* p = head; p != NULL; p = p->next) {
        if (p->rad > threshold) {
            result = push_front(result, p->date, p->rad);
        }
    }

    return result;
}