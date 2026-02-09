#https://pl.spoj.com/problems/PRIME_T/
def prime_numer(number: int) -> str:
    if number < 2:
        return "NIE"
    x = 2
    while x*x <= number:
        if number % x == 0:
            return "NIE"
        x += 1
    return "TAK"
def main() -> None:
    t = int(input())
    for _ in range(t):
        n = int(input())
        print(prime_numer(n))
if __name__ == "__main__":
    main()