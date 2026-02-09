/*
Napisz program, który sprawdzi, czy trzy podane przez użytkownika liczby całkowite mogą być długościami boków trójkąta prostokątnego. 
Liczby wprowadzane są w dowolnej kolejności. 
Program powinien najpierw ustalić, która z nich jest największa i potraktować ją jako przeciwprostokątną, 
a następnie sprawdzić, 
czy suma kwadratów dwóch pozostałych boków jest równa kwadratowi tej największej liczby. 
Jeśli warunek Pitagorasa jest spełniony, program wyświetla komunikat, że z podanych długości można zbudować trójkąt prostokątny. 
W przeciwnym przypadku należy poinformować, że liczby nie tworzą trójki pitagorejskiej.
a^2 + b^2  = c^2
*/
#include <stdio.h>
int max(int x,int y,int z){
    int m = x;
    if (y > m) m = y;
    if (z > m) m = z;
    return m;
}
int main(){
    int a,b,c;
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);
    int C = max(a,b,c);
    if (a*a + b*b + c*c - C * C == C*C){printf("Trojkat jest prostokatny");}
    else {printf("Trojkat nie jest prostokatny");}
}