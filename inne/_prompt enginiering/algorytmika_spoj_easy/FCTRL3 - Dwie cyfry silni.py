#https://pl.spoj.com/problems/FCTRL3/
# Zadanie
# Napisz program, który:
# wczyta ze standardowego wejścia nieujemną liczbę całkowitą n,
# policzy cyfrę dziesiatek oraz cyfrę jedności w zapisie dziesiętnym liczby n!,
# wypisze wynik na standardowe wyjście.
# Wejście
# W pierwszej linii wejścia znajduje się jedna liczba całkowia D (1≤D≤30), oznaczjąca liczbę przypadków do rozważenia. Opis każdego przypadku składa się z jednej linii, w której znajduje się jedna nieujemna liczba całkowita n (0 ≤ n ≤ 1 000 000 000).

# Wyjście
# Dla każdego przypadku z wejścia. Twój program powinien wypisać w osobnej linii dokładnie dwie cyfry (oddzielone pojedynczą spacją): cyfrę dziesiątek i cyfrę jedności liczby n! zapisanej w systemie dziesiętnym.

def factorial(number: int) -> int:
    result = number
    for i in range(2,number):
        result = result * i % 100
    return result

def dec_and_digit(number: int) -> tuple[int,int]:
    digit = number % 10
    dec = number % 100 // 10
    return (dec,digit)

def main() -> None:
    t = int(input())
    for _ in range(t):
        n = int(input())
        n = n or 1
        if n >= 10:
            print(0,0) 
        else:
            print(*dec_and_digit(factorial(n)))

if __name__ == "__main__":
    main()

