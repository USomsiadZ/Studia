/*
woim zadaniem jest stworzenie klasy, która symuluje działanie karty kredytowej z limitem operacji. Karta powinna udostępniać podstawowe operacje finansowe:

dokonanie płatności,
spłatę zadłużenia,
sprawdzenie dostępnego limitu kredytowego.
Każda karta ma określony maksymalny limit kredytowy oraz limit liczby operacji na dzień. Upływ czasu możesz symulować udostępniając metodę pozwalającą na zresetowanie dziennego licznika operacji.

Karta powinna przechowywać wszystkie informacje niezbędne do wykonania powyższy operacji, a ponadto:

numer karty (generowany losowo),
dane o właścicielu karty.
Wskazówki
Karta powinna odpowiadać za obsługę swoich operacji i kontrolę poprawności (walidacja parametrów, zapewnienie spójności stanu, egzekwowanie reguł biznesowych).
Możesz zdecydować w jaki sposób reagować na niepoprawne operacje.
Pamiętaj o oddzieleniu interfejsu od implementacji - klient powinien korzystać z oferowanych operacji, nie znając szczegółów reprezentacji.
Pamiętaj o ochronie stanu obiektu - nie wszystko powinno być dostępne bezpośrednio z zewnątrz.
Testy
W funkcji main przygotuj scenariusze testowe pokazujące użycie obiektu (zarówno te poprawne, jak i reakcję na niedozwolone operacje).

UML
Przed implementacją narysuj diagram UML przedstawiający strukturę klasy.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOP.zajecia4
{
    class Karta
    {
        private int Limit_dzienny;
        private int Limit_kredytowy;
        private int Liczba_operacji;
        private string Numer_karty;
        private string Wlasciciel;
        private int Saldo;
        public Karta(int limit_dzienny = 10, int limit_kredytowy = 1000, string wlasciciel = "", int liczba_operacji = 0)
        {
            Random random = new Random();
            Numer_karty = "1234567890";//Todo random
            Limit_dzienny = limit_dzienny;
            Limit_kredytowy = limit_kredytowy;
            Liczba_operacji = liczba_operacji;
            Wlasciciel = wlasciciel;
            Saldo = 0;
        }
        public void wypłaty(int kwota)
        {
            //todo sprawdzenie czy nie przekracza limitu
            //Liczba_operacji++;
            Console.WriteLine($"Wypłata: {kwota}");
            Saldo -= kwota;
            saldo();
        }
        public void wpłaty(int kwota)
        {
            Console.WriteLine($"Wpłata: {kwota}");
            Saldo += kwota;
            saldo();
        }
        //public void Spłata_zadluzenia(int kwota);//Todo 
        public void Sprawdzenie_dostepnego_limitu_kredytowego()
        {
            Console.WriteLine($"Dostępny limit kredytowy: {Limit_kredytowy}");
            Console.WriteLine($"Saldo: {Saldo}");
        }
        public void saldo()
        {
            Console.WriteLine($"Saldo: {Saldo}");
        }
    }
    public class Program
    {
        public static void Main()
        {
            Karta jan = new(wlasciciel: "Jan kowalski", liczba_operacji: 20);
            jan.saldo();
            jan.wpłaty(50);
            jan.wypłaty(25);
            jan.wypłaty(150);

        }
    }
}