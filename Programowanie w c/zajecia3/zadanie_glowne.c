/*
Jest statek. Na jego pokładzie agenci wymieniają między sobą zaszyfrowane wiadomości, jednak z powodu ograniczeń systemu łączności mogą przesyłać jednorazowo nie więcej niż 128 znaków.
Program powinien umożliwiać wprowadzenie dwóch tajnych wiadomości i wykonanie na nich następujących operacji:

Odczyt długości transmisji
Każda wiadomość musi zostać dokładnie zmierzona — system powinien wyświetlić długość obu wprowadzonych komunikatów, aby agenci mogli oszacować wielkość szyfrowanych danych.

Sprawdzenie zgodności przekazu
Czasami różne sekcje Oriona przesyłają odmienne wersje tego samego komunikatu. System ma porównać dwie wiadomości i sprawdzić, czy są one identyczne, ignorując przy tym różnice w wielkości liter.

Scalenie transmisji
W razie potrzeby agenci mogą połączyć dwa komunikaty w jeden dłuższy. Program ma utworzyć nową wiadomość, powstałą przez połączenie obu tekstów, i wyświetlić wynikową transmisję.

Szyfrowanie metodą ROT13
W trosce o bezpieczeństwo danych agenci korzystają z klasycznego algorytmu ROT13. Program powinien zaszyfrować pierwszą wprowadzoną wiadomość, zastępując każdą literę alfabetu łacińskiego (a–z, A–Z) literą przesuniętą o 13 pozycji w alfabecie (cyklicznie).
Przykład:

Wejście:  Ala ma piłkę?
Wynik:    Nyn zn cvłxę?
Znaki spoza alfabetu pozostają bez zmian.
(Uwaga: ponowne zastosowanie ROT13 na wyniku przywraca oryginalny tekst).

Odczyt wsteczny
W pewnych sytuacjach agenci Oriona muszą odczytać wiadomość przesłaną od końca. Program powinien odwrócić pierwszą wprowadzoną wiadomość i wyświetlić ją w tej postaci.

Po wczytaniu dwóch wiadomości program powinien wyświetlić menu operacji, z którego użytkownik może wybierać odpowiednie polecenia, np.:

=== TERMINAL ORION ONE ===
1. Wyświetl długość obu wiadomości
2. Porównaj wiadomości
3. Połącz wiadomości
4. Szyfruj wiadomość 1 (ROT13)
5. Odwróć wiadomość 1
0. Zakończ transmisję
Wybierz opcję: 
Menu powinno działać w pętli, umożliwiając agentowi wykonywanie wielu operacji bez ponownego uruchamiania programu.
Wybór opcji 0 kończy działanie systemu i wyświetla komunikat o zakończeniu sesji transmisyjnej.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int menu() {
    int wybor;
    printf("\n\n\n\n=== TERMINAL ORION ONE ===\n");
    printf("1. Wyswietl dlugosc obu wiadomosci\n");
    printf("2. Porownaj wiadomosci (bez uwzgledniania wielkosci liter)\n");
    printf("3. Polacz wiadomosci\n");
    printf("4. Szyfruj wiadomosc 1 (ROT13)\n");
    printf("5. Odwroc wiadomosc 1\n");
    printf("0. Zakoncz transmisje\n");
    printf("Wybierz opcje: \n\n\n");
    scanf("%d", &wybor);
    return wybor;
}
int dlugosc_transmisji(char w1[128],char w2[128]){
    printf("Dlugosc widomosci nr 1 to %zu\n",strlen(w1));
    printf("Dlugosc widomosci nr 2 to %zu\n",strlen(w2));
    return 0;
}
int czy_zgodne(char w1[128], char w2[128]) {
    if (strlen(w1) != strlen(w2)){
        printf("Dlugosc nie jest zgodna");
        return 0;}
    for (int i = 0; i < strlen(w1); i++) {
        if (tolower(w1[i]) != tolower(w2[i])){
            printf("Nie są zgodne\n");
            return 0;
            }
        else{
            printf("Są zgodne\n");
            return 1;
        }
            
    
}
}
int scalenie(char w1[128],char w2[128]){
    char scalony[256];
    strcpy(scalony,w1);
    strcat(scalony,w2);
    printf("%s\n",scalony);
}
int rot13(char w1[128]){// zamiast sizeof strlen

    for(int i=0;i< strlen(w1);i++){
        char c = w1[i];
        if (c >= 'A' && c <= 'Z') {
            w1[i] = 'A' + ((c - 'A' + 13) % 26);
        }
        else if (c >= 'a' && c <= 'z') {
            w1[i] = 'a' + ((c - 'a' + 13) % 26);
        }
    }
    printf("Zaszyfrowana wiadomosc to %s\n",w1);
}
int odwrot(char w1[128]){
    int dlugosc1 = strlen(w1);
    char m;
    for(int i=0;i< dlugosc1/2;i++){
        m = w1[i];
        w1[i]= w1[dlugosc1-i-1];
        w1[dlugosc1-i-1] = m;
    }
    printf("Odwrocona wiadomosc to %s\n",w1);
}


int main(){
char wiadomosc1[128];
char wiadomosc2[128];
int wybor;
printf("Pierwsza wiadomosc:");
scanf(" %127[^\n]", wiadomosc1);

printf("Druga wiadomosc:");
scanf(" %127[^\n]", wiadomosc2);
while(1){
    wybor = menu();
    switch (wybor)
    {
        case 1: dlugosc_transmisji(wiadomosc1,wiadomosc2);break;
        case 2: czy_zgodne(wiadomosc1,wiadomosc2);break;
        case 3: scalenie(wiadomosc1,wiadomosc2);break;
        case 4: rot13(wiadomosc1);break;
        case 5: odwrot(wiadomosc1);break;
        case 0: exit(0);break;
    }


}
return 0;
}