/*
Twoim zadaniem jest stworzenie klasy, która symuluje działanie karty kredytowej z limitem operacji. Karta powinna udostępniać podstawowe operacje finansowe:

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



#nullable enable
using System;
using System.Linq;
namespace OOP.zajecia4
{
    class Karta
    {
        private int Limit_operacji_dzienny;
        private int Liczba_operacji = 0;
        private int Limit_kredytowy = 1000;
        private int Numer_karty;
        public string? Wlasciciel { get; }
        private double Saldo = 0;
        private int Dzien = 0;
        private bool CzyLimit => Liczba_operacji < Limit_operacji_dzienny;

        public Karta(int limit_operacji_dzienny = 10, string wlasciciel = "")
        {
            if (string.IsNullOrEmpty(wlasciciel))
            {
                throw new Exception("Nie podano właściciela");
            }
            Numer_karty = new Random().Next(1000, 9999);
            Wlasciciel = wlasciciel;
            Limit_operacji_dzienny = limit_operacji_dzienny;
        }

        public void WykonajWypłaty(double kwota)
        {
            if (Saldo + Limit_kredytowy > kwota && CzyLimit)
            {
                Saldo -= kwota;
                Liczba_operacji++;
                Console.WriteLine($"Udało się wypłacić {kwota}");
            }
            else if (!CzyLimit)
            {
                Console.WriteLine("Osiągnięto limit operaci");
            }
        }
        public void WykonajWpłaty(double kwota)
        {
            if (CzyLimit)
            {
                Saldo += kwota;
                Liczba_operacji++;
                Console.WriteLine($"Wpłacono: {kwota}");
            }
            else
            {
                Console.WriteLine("Osiągnięto limit operacji");
            }

        }
        public void Spłata_zadluzenia(double kwota)
        {
            if (Saldo < 0 && CzyLimit)
            {
                Saldo += kwota;
                Console.WriteLine($"Spłacono zadłużenie w kwocie {kwota}");
            }
            else if (!CzyLimit)
            {
                Console.WriteLine("Osiągnięto limit operaci");
            }
            else
            {
                Console.WriteLine("Brak zadłużenia");
            }

        }
        public void SprawdzSaldo()
        {
            Console.WriteLine($"Saldo wynosi {Saldo}");
        }
        public void SprawdzLimit()
        {
            if (Saldo > 0)
            {
                Console.WriteLine($"Limit kredytowy: {Limit_kredytowy}");
            }
            else
            {
                Console.WriteLine($"Limit kredytowy: {Limit_kredytowy + Saldo}");
            }
        }
        public void NowyDzien()
        {
            Dzien++;
            Liczba_operacji = 0;
            if (Saldo < 0) Saldo *= 1.1;
            Console.WriteLine("Nastał nowy dzień");
        }
        public void SprawdzDzien()
        {
            Console.WriteLine($"Dzien: {Dzien}");
        }
        public void SprawdzLiczbeOperacji()
        {
            Console.WriteLine($"Liczba operacji: {Liczba_operacji}");
        }
        //* Dodatkowa rzecz
        public void Platnosc_z_cashback(string sklep, int kwota)
        {
            string[] tab = ["Biedronka", "Lidl", "Karfour"];
            double[] cashback = [0.99, 0.98, 0.97];
            if (!tab.Contains(sklep))
            {
                Console.WriteLine("Nie ma takiego sklepu");
                return;
            }
            else if (Saldo + Limit_kredytowy > kwota && CzyLimit)
            {
                int index = Array.IndexOf(tab, sklep);
                Saldo -= kwota * cashback[index];
                Liczba_operacji++;
                Console.WriteLine($"Udało się wypłacić {kwota} z cashback {cashback[tab.IndexOf(sklep)]}%");
            }
            else if (!CzyLimit)
            {
                Console.WriteLine("Osiągnięto limit operaci");
            }

        }
    }

    public class Program
    {
        public static void Main()
        {
            Karta janek = new(10, "janek");
            /*janek.WykonajWypłaty(100);
            janek.WykonajWpłaty(50);
            janek.Spłata_zadluzenia(10);
            janek.SprawdzSaldo();
            janek.NowyDzien();
            janek.SprawdzSaldo();
            janek.WykonajWypłaty(100);
            janek.WykonajWpłaty(50);
            janek.Spłata_zadluzenia(10);
            janek.SprawdzSaldo();
            janek.SprawdzLimit();*/
            /*for (int i = 0; i < 11; i++)
            {
                janek.WykonajWypłaty(1);
            }*/
            janek.NowyDzien();
            janek.SprawdzSaldo();
            janek.Platnosc_z_cashback("Biedronka", 50);
            janek.SprawdzSaldo();
        }
    }
}