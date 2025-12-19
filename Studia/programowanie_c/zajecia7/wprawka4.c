#include <stdio.h>
#include <stdlib.h>

/*
Biblioteczne funkcje obsługi napisów w C zakładają, że łańcuch docelowy ma wystarczająco duży rozmiar, by pomieścić wynik operacji, co nie zawsze jest prawdą. Napisz własne "bezpieczne" implementacje następujących funkcji, dbając o odpowiednią zmianę rozmiaru łańcucha wynikowego: 

char* newStrcpy (char* destination, const char* source);
char* newStrncpy (char* destination, const char* source, int n);
char* newStrcat(char * destination, const char * source); - Scala dwa łańcuchy znaków w jeden. Zwraca zmodyfikowany łańcuch.
char* newStrncat(char * destination, const char * source, int n); - Scala dwa łańcuchy znaków w jeden. Uwzględnia maksymalną liczbę znaków, jaka może zostać dopisana. Zwraca zmodyfikowany łańcuch.

*/

// Strcpy 
// Liczy bez konca \0 ,czyli aaa\0 -> 3
int count(const char *tab) {
    int i = 0;
    if (!tab) return 0;
    
    while (*(tab + i) != '\0') {
        i++;
    }
    return i;   
}

char* newStrcpy(char* destination, const char* source) {
    if (!source) return NULL;
    
    int size = count(source) + 1;
    char *p = realloc(destination, size * sizeof(char));
    if (!p) return NULL;
    
    destination = p;
    for (int i = 0; i < size; i++) {
        *(destination + i) = *(source + i);
    }
    return destination;
}

char* newStrncpy(char* destination, const char* source, int n) {
    // Zalozenie: newStrncpy nie zeruje reszty bajtow
    if (!source) return NULL;
    
    int size = n + 1;
    char *p = realloc(destination, size * sizeof(char));
    if (!p) return NULL;
    
    destination = p;
    int i = 0;
    for (; i < n && source[i] != '\0'; i++) {
        *(destination + i) = *(source + i);
    }
    *(destination + i) = '\0';
    return destination;
}

char* newStrcat(char* destination, const char* source){
    if(!source)return NULL;
    int size_destination = destination ? count(destination) : 0;
    int size_source = count(source);

    char *p = realloc(destination,(size_destination + size_source + 1) * sizeof *p);
    if(!p)return NULL;
    destination = p;
    int i = 0;
    for (; i < size_source; i++)
    {
        destination[i + size_destination] = source[i];
    }
    destination[size_destination + size_source] = '\0';
    return destination;
}

int min(int a,int b){return (a < b) ? a : b;}

char* newStrncat(char* destination, const char* source, int n){
    if(!source)return NULL;
    int size_destination = destination ? count(destination) : 0;
    int size_source = count(source);

    char *p = realloc(destination,(size_destination + min(size_source,n) + 1) * sizeof *p);
    if(!p)return NULL;
    destination = p;
    int i = 0;
    for (; i < n && i < size_source; i++)
    {
        destination[i + size_destination] = source[i];
    }
    destination[size_destination + min(size_source,n)] = '\0';
    return destination;
}

int main() {
    const char *tekst = "test";
    const char *tekst2 = "----";
    int size = 10;
    char *tab = malloc(size * sizeof *tab);
    if (!tab) {
        printf("Malloc ERROR");
        return 1;
    }
    
    int wybor = 4;
    
    // Kopiowanie
    switch (wybor) {
    case 1:{
        char *tmp = newStrcpy(tab,tekst);
        if (!tmp) {
            free(tab);
            return 1;
        }
        tab = tmp;
        printf("%s\n", tab);
        break;
    }
    case 2:{
        char *tmp = newStrncpy(tab,tekst,2);
        if (!tmp) {
            free(tab);
            return 1;
        }
        tab = tmp;
        printf("%s\n", tab);
        break;
    }
    case 3:{
        tab[1] = '\0';
        tab[0] = '-';
        char *tmp = newStrcat(tab, tekst);
        if (!tmp) {
            free(tab);
            return 1;
        }
        tab = tmp;
        printf("%s\n", tab);
        break;
    }
    case 4:{
        tab[4] = '\0';
        tab[3] = 't';
        tab[2] = 's';
        tab[1] = 'e';
        tab[0] = 't';
        char *tmp = newStrncat(tab, tekst2, 3);
        if (!tmp) {
            free(tab);
            return 1;
        }
        tab = tmp;
        printf("%s\n", tab);
        break;
    }
    }


    free(tab);
    tab = NULL;
    return 0;
}