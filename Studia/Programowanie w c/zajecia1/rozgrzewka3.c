/* 
Napisz program, który wczyta liczbę całkowitą oznaczającą rok.
Następnie sprawdzi, czy ten rok jest przestępny, czy nie, i poda odpowiednią informację.
Zasada:
	•	Rok jest przestępny, jeśli dzieli się przez 4,
	•	ale jeśli dzieli się przez 100, to nie jest przestępny,
	•	wyjątek: jeśli dzieli się przez 400, to jednak jest przestępny.
*/
#include <stdio.h>
int main(){
    int rok;
    printf("Podaj rok\n");
    scanf("%d",&rok);
    if(rok % 400 == 0){printf("Rok jest przestepny");}
    else if (rok % 100 == 0){printf("Rok nie jest przestepny");}
    else if (rok % 4 == 0){printf("Rok jest przestepny");}
    else {printf("Rok nie jest przestepny");}

}