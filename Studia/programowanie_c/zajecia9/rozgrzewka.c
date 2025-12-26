/*
W Akademii Technomagii w mieście Aerendell adepci uczą się praktycznych umiejętności łączenia magii z inżynierią. Jednym z podstawowych przedmiotów jest Praktyka Operacji na Plikach, prowadzona przez Archiwistkę Seris Valenne.
Twoim celem jest rozwiązanie poniższych problemów:

Problem 1
W magazynie Akademii znajduje się plik zwany Rejestrem Wartości, zapisany na kryształowym dysku. Zawiera on rzeczywiste liczby z pomiarów energii magicznej.
Archiwistka Seris prosi: „Musisz odczytać cały plik i rozdzielić dane na dwie osobne księgi: rejestr energii dodatniej oraz rejestr energii ujemnej."

Problem 2
W bibliotece Akademii znajduje się zwój z zapisami dawnych badań. Niestety pojawił się w nim błąd: stare, niewłaściwe określenie występuje wiele razy i trzeba je zastąpić innym, obecnie akceptowalnym słowem.
Archiwistka Seris mówi: „Twoim zadaniem jest odczytanie każdego słowa z pliku wejściowego i przepisanie go do nowego pliku, ale gdy natrafisz na słowo dokładnie równe s1, zastąp je słowem s2.”

Problem 3
W laboratoriach Technomagii wykorzystuje się Artefakty Losowe, czyli pliki binarne przechowujące losowe wartości typu float, będące odczytami gęstości artefaktu z pewnego przedziału czasowego. Są później analizowane w eksperymentach.
Seris zleca: „Stwórz plik binarny i zapisz w nim n losowych liczb mieszczących się w podanym przedziale.”

Problem 4
Zadaniem adepta jest odczytanie wskazanego Artefaktu Losowego.
Archiwistka instruuje: „Wczytaj wszystkie wartości do dynamicznie alokowanej tablicy (zaklęcia fread możesz użyć tylko jednokrotnie) a następnie oblicz średnią.”
*/
/*
* Problem 1 - Rejestr Wartości
* Problem 2 - Zwój Badań
* Problem 3 - Artefakt Losowy
* Problem 4 - Odczytanie Artefaktu Losowego
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int problem1(){
    FILE *file = fopen("rejestr_wartosci.txt","r");
    if(file == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }
    FILE *file_positive = fopen("rejestr_wartosci_dodatnie.txt","w");
    FILE *file_negative = fopen("rejestr_wartosci_ujemne.txt","w");
    if(file_positive == NULL || file_negative == NULL){
        printf("Nie udało się otworzyć plików wyjściowych\n");
        fclose(file);
        if(file_positive) fclose(file_positive);
        if(file_negative) fclose(file_negative);
        return 1;
    }
    float value;
    while(fscanf(file,"%f",&value) != EOF){
        if(value > 0){
            fprintf(file_positive,"%f\n",value);
        }else{
            fprintf(file_negative,"%f\n",value);
        }
    }

    fclose(file_positive);
    fclose(file_negative);
    fclose(file);
    return 0;
}
int problem2(char s1[128], char s2[128]){
    FILE *file = fopen("zwoj_badan.txt","r");
    if(file == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }
    
    FILE *file_new = fopen("zwoj_badan_new.txt","w");
    if(file_new == NULL){
        printf("Nie udało się otworzyć pliku\n");
        fclose(file);
        return 1;
    }

    char word[128];
    int first = 1;
    while(fscanf(file,"%s",word) != EOF){
        if(!first) fprintf(file_new, " ");
        first = 0;
        
        if(strcmp(word,s1) == 0){
            fprintf(file_new,"%s",s2);
        }else{
            fprintf(file_new,"%s",word);
        }
    }
    fclose(file);   
    fclose(file_new);
    return 0;
}
int problem3(int n, float min, float max){
    FILE *file = fopen("artefakt_losowy.bin","wb");
    if(file == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }    
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        // rand() <0,RAND_MAX> -> <0,1>;<0,1>*(max-min) -> <0,max-min>;<0,max-min>+min -> <min,max>
        float value = (float)rand()/RAND_MAX * (max - min) + min;
        fwrite(&value,sizeof(float),1,file);
    }
    fclose(file);
    return 0;
}
float problem4(int n){
    FILE *file = fopen("artefakt_losowy.bin","rb");
    if(file == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return -1.0;
    }
    float *tab = malloc(n * sizeof(float));
    if(tab == NULL){
        printf("Nie udało się zaalokować pamięci\n");
        fclose(file);
        return -1.0;
    }
    fread(tab,sizeof(float),n,file);
    float average = 0;
    for(int i = 0; i < n; i++){
        average += tab[i];
    }
    average /= n;
    free(tab);
    fclose(file);
    return average;
}
void show_menu(){
    printf("1) Problem 1\n");
    printf("2) Problem 2\n");
    printf("3) Problem 3\n");
    printf("4) Problem 4\n");
    printf("0) Wyjście\n");
}
int main(){
    char s1[128], s2[128];
    int n;
    float min, max;
    while(1){
        show_menu();
        int problem;
        scanf("%d",&problem);
        switch (problem) {
            case 1:
                problem1();
                break;
            case 2:
                printf("Podaj słowo do zastąpienia: ");
                scanf("%s",s1);
                printf("Podaj słowo na jego miejsce: ");
                scanf("%s",s2);
                problem2(s1,s2);
                break;
            case 3:
                printf("Podaj liczbę elementów: ");
                scanf("%d",&n);
                printf("Podaj minimalną wartość: ");
                scanf("%f",&min);
                printf("Podaj maksymalną wartość: ");
                scanf("%f",&max);
                problem3(n,min,max);
                break;
            case 4:
                printf("Podaj liczbę elementów: ");
                scanf("%d",&n);
                float average = problem4(n);
                printf("Średnia: %f\n",average);
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("Nieznany problem\n");
                break;
        }
    }
    return 0;
}
