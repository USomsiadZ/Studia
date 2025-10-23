/*
Statek kosmiczny Orion One prowadzi misję badawczą w odległym układzie planetarnym. Jego komputer pokładowy analizuje dane z czujników rozmieszczonych w różnych sekcjach statku. Twoim zadaniem jest przygotowanie programu symulującego uproszczony system diagnostyczny, który pozwala wczytywać dane z czujników, kalibrować je oraz wykrywać i naprawiać błędne odczyty.

Program powinien przechowywać dane pomiarowe w tablicy liczb typu double
i udostępniać użytkownikowi menu pozwalające na wykonywanie kolejnych operacji.

Użytkownik powinien mieć możliwość:

wczytania danych z czujników,
wyświetlenia odczytów,
przeprowadzenia kalibracji,
naprawienia błędnych odczytów,
modyfikacji pojedynczego odczytu,
zakończenia działania programu.
Zaimplementuj poniższe funkcje:

void showIntro();
Wyświetla powitanie, nazwę statku i autora programu. Nie przyjmuje żadnych parametrów i nie zwraca wartości.

int showMenu();
Wyświetla menu główne programu, pobiera wybór użytkownika i zwraca jego numer. Powinna sprawdzać poprawność danych wejściowych.

void readSensors(double sensors[], int n);
Wczytuje dane z czujników, prosząc użytkownika o n wartości. Każdy odczyt powinien być sprawdzony pod względem poprawności – czy mieści się w przyjętym zakresie (np. od –100 do 200). Do walidacji można wykorzystać funkcję readValue() (opisaną niżej).

void displaySensors(double sensors[], int n); 
Wyświetla bieżące dane pomiarowe w czytelnej formie.

void calibrateSensors(double sensors[], int n, double offset);
Dodaje do każdego odczytu wartość offset, aby zasymulować kalibrację czujników.

int findFaultySensor(double sensors[], int n, double minAllowed, double maxAllowed);
Wyszukuje pierwszy czujnik, którego odczyt wychodzi poza dopuszczalny zakres <minAllowed, maxAllowed)>. Zwraca jego indeks lub -1, jeśli wszystkie odczyty są poprawne.

void modifySensor(double sensors[], int n, int index);
Pozwala ręcznie zmienić odczyt wybranego czujnika. Funkcja powinna wyświetlić numer czujnika i jego bieżącą wartość, poprosić o wprowadzenie nowej wartości (z walidacją) oraz zastąpić starą wartość nową. 

int readValue(double *value, double min, double max);
Wczytuje pojedynczą wartość typu double przez wskaźnik. Sprawdza, czy wprowadzona liczba mieści się w zakresie <min, max>. Zwraca 0 w przypadku błędu. 
Funkcja może być wykorzystywana:
przy wypełnianiu tablicy w readSensors,
przy ręcznej zmianie odczytu (modifySensor),
przy wprowadzaniu wartości offset do kalibracji.

*/
#include <stdio.h>
void showIntro(){
    puts("Witaj na statku orion");
    puts("Autor Hubert Parzych");
}
int showMenu(){
    int wybor = 0;
    puts("1. Wczytanie dane z czujnikow");
    puts("2. Wyświetalnie odczytow");
    puts("3. Przeprowadzenie kalibracji");
    puts("4. Naprawianie blednych odczytow");
    puts("5. Modyfikacja pojedynczego odczytu");
    puts("6. Zakonczenie programu");
    scanf("%d",&wybor);
    if(wybor <= 6 && wybor >= 1){
        return wybor;
    }
    else{
        puts("Zle podany input");
        while (getchar() != '\n');
        return showMenu();
    }
    
}
void readSensors(double sensors[], int n){
    for(int i = 0; i < n;i++){
        printf("Podaj %d wartosc \n",i);
        scanf("%lf",&sensors[i]);
    }
}
void displaySensors(double sensors[], int n){
    for(int i = 0; i < n;i++){
        printf("Dane nr %d to %lf\n", i, sensors[i]);
    }
}   
void calibrateSensors(double sensors[], int n, double offset){
    for(int i = 0; i < n; i++) {
        sensors[i] += offset;
    }
}
int findFaultySensor(double sensors[], int n, double minAllowed, double maxAllowed){
    for(int i = 0; i < n; i++){
        if (sensors[i] < minAllowed || sensors[i] > maxAllowed) {
            return i;
        }
    }
    return -1;
}
void modifySensor(double sensors[], int n, int index){
    double wartosc;
    printf("Stara wartosc %lf\n",sensors[index]);
    puts("Wprowadz nowa wartosc\n");
    scanf("%lf",&wartosc);
    sensors[index] = wartosc;

}

int main(){
    double offset;
    double dane[128] = {1,2};
    int ilosc_danych;
    showIntro();
    while (1) {
        int wybor = showMenu();
        switch (wybor) {
            case 1:
                puts("Podaj ilosc danych");
                scanf("%d",&ilosc_danych);
                readSensors(dane, ilosc_danych);
                break;
            case 2:
                displaySensors(dane, ilosc_danych);
                break;
            case 3:
                printf("Podaj offset kalibracji: ");
                scanf("%lf", &offset);
                calibrateSensors(dane, ilosc_danych, offset);
                break;
            case 4: {
                int faulty = findFaultySensor(dane, ilosc_danych, -100, 200);
                if (faulty != -1)
                    printf("Błędny czujnik: %d\n", faulty);
                else
                    puts("Brak błędnych czujników.");
                break;
            }
            case 5: {
                int index;
                printf("Podaj numer czujnika do zmiany: ");
                scanf("%d", &index);
                if (index >= 0 && index < 128)
                    modifySensor(dane, ilosc_danych, index);
                else
                    puts("Niepoprawny numer czujnika.");
                break;
            }
            case 6:
                puts("Zakończono program.");
                break;
            default:
                puts("Niepoprawny wybór.");
                break;
        }
        if (wybor == 6) break;
    }
    return 0;
}
