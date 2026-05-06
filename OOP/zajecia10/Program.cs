/*
Twoim zadaniem jest zaprojektowanie mechanizmu reprezentującego wynik operacji, która może zakończyć się powodzeniem lub błędem.

Wymagania
Zaprojektuj klasę generyczną (lub szablon w C++), która:

reprezentuje wynik operacji,
może przechowywać wartość dowolnego typu (dla operacji zakończonej sukcesem),
przechowuje informację, czy operacja się powiodła,
w przypadku błędu pozwala również na przechowanie informacji o jego przyczynie.
Scenariusz testowy
Założmy prosty model systemu rezerwacji biletów lotniczych. Będzie on zawierać trzy metody symulujące kolejne kroku zakupu biletu:

Wyszukanie połączenia
na podstawie podanego miasta wylotu, miasta przylotu oraz dnia lotu zwraca odnalezione połączenie (np. obiekt klasy Flight)
operacja może zakończyć się niepowodzeniem, jeśli nie określono poprawnie wszystkich danych albo nie ma połączenia na danej trasie
Dokonanie rezerwacji
na podstawie przekazanego połączenia oraz informacji o liczbie pasażerów i wadze bagażu zwracana jest kwota do zapłaty
sytuacje błędne mogą wynikać z braku odpowiedniej liczby dostępnych miejsc lub przekroczonego limitu bagażu
Wykonanie płatności
dane wejściowe to kwota i numer karty
wynik to string z numerem potwierdzenia operacji
sytuacje błędne to niepoprawne dane wejściowe lub brak środków na karcie
Operacje w sytuacjach błędnych nie rzucają wyjątków, ale za każdym razem zwracając odpowiedź zapakowaną w generyczny kontener.

Nie pisz kompletnego systemu, a jedynie mock, który będzie generować odpowiedź na podstawie jakichś prostych reguł. Możesz ponadto zwracać błąd w sytuacjach losowych, symulując wewnętrzne błędy systemu lub np. przeciążenie sieci.

W kodzie klienta:
pokaż użycie zaprojektowanego rozwiązania,
obsłuż zarówno przypadki sukcesu, jak i błędu,
pokaż przykładowy scenariusz rezerwacji (np. wyszukanie - rezerwacja - płatność).
UML
Narysuj diagram UML przedstawiający zaprojektowane klasy oraz ich relacje.
/*
Klasa - 3 pola(udałosię/nieudało,ile wynik wynosi,tekst jeśli wyniku nie udało się wyprodukować)
konstruktor prywatny ale 2 metody statyczne wywoływane z klasy np sukces - obiekt klasy generycznej;porażka - error message (tekst)
*/

#nullable enable
using System;

// ----Generyczny kontener wyniku----
public class Wynik<T>
{
    public bool Sukces { get; }
    public T? Wartosc { get; }
    public string? Blad { get; }

    private Wynik(bool sukces, T? wartosc, string? blad)
    {
        Sukces = sukces;
        Wartosc = wartosc;
        Blad = blad;
    }

    public static Wynik<T> Ok(T wartosc) => new Wynik<T>(true, wartosc, null);
    public static Wynik<T> Porazka(string blad) => new Wynik<T>(false, default, blad);
}

// ----Model lotu----
public class Lot
{
    public string Skad { get; }
    public string Dokad { get; }
    public DateTime Dzien { get; }
    public decimal Cena { get; }
    public int WolneMiejsca { get; }
    public int LimitBagazu { get; }

    public Lot(string skad, string dokad, DateTime dzien, decimal cena, int wolneMiejsca, int limitBagazu)
    {
        Skad = skad;
        Dokad = dokad;
        Dzien = dzien;
        Cena = cena;
        WolneMiejsca = wolneMiejsca;
        LimitBagazu = limitBagazu;
    }

    public override string ToString() => $"{Skad} -> {Dokad} ({Dzien:yyyy-MM-dd}), cena={Cena}";
}

// ----System rezerwacji----
public class Rezerwacje
{
    private Random rng = new Random();

    public Wynik<Lot> Szukaj(string skad, string dokad, DateTime dzien)
    {
        if (string.IsNullOrEmpty(skad) || string.IsNullOrEmpty(dokad))
            return Wynik<Lot>.Porazka("Brak danych wejściowych.");
        if (skad == dokad)
            return Wynik<Lot>.Porazka($"Brak połączenia {skad} -> {dokad}.");
        if (rng.Next(10) == 0)
            return Wynik<Lot>.Porazka("Przeciążenie sieci.");

        return Wynik<Lot>.Ok(new Lot(skad, dokad, dzien, 500, 3, 30));
    }

    public Wynik<decimal> Rezerwuj(Lot lot, int pasazerow, int bagaz)
    {
        if (pasazerow <= 0)
            return Wynik<decimal>.Porazka("Niepoprawna liczba pasażerów.");
        if (pasazerow > lot.WolneMiejsca)
            return Wynik<decimal>.Porazka("Brak wolnych miejsc.");
        if (bagaz > lot.LimitBagazu)
            return Wynik<decimal>.Porazka("Przekroczono limit bagażu.");

        return Wynik<decimal>.Ok(lot.Cena * pasazerow);
    }

    public Wynik<string> Zaplac(decimal kwota, string karta)
    {
        if (kwota <= 0)
            return Wynik<string>.Porazka("Niepoprawna kwota.");
        if (string.IsNullOrEmpty(karta) || karta.Length != 16)
            return Wynik<string>.Porazka("Niepoprawny numer karty.");
        if (rng.Next(5) == 0)
            return Wynik<string>.Porazka("Brak środków na karcie.");

        return Wynik<string>.Ok($"POT-{rng.Next(100000, 999999)}");
    }
}

class Program
{
    static void Main()
    {
        Rezerwacje r = new Rezerwacje();

        // ---- Scenariusz: szukaj -> rezerwuj -> zapłać ----
        Wynik<Lot> lot = r.Szukaj("Warszawa", "Kraków", new DateTime(2026, 6, 15));
        if (!lot.Sukces) { Console.WriteLine("Błąd: " + lot.Blad); return; }
        Console.WriteLine("Znaleziono: " + lot.Wartosc);

        Wynik<decimal> rez = r.Rezerwuj(lot.Wartosc!, 2, 20);
        if (!rez.Sukces) { Console.WriteLine("Błąd: " + rez.Blad); return; }
        Console.WriteLine("Do zapłaty: " + rez.Wartosc);

        Wynik<string> pay = r.Zaplac(rez.Wartosc, "1234567890123456");
        if (!pay.Sukces) { Console.WriteLine("Błąd: " + pay.Blad); return; }
        Console.WriteLine("Potwierdzenie: " + pay.Wartosc);

        // ---- Błędne scenariusze ----
        Console.WriteLine("\n----- Błędy -----");
        Console.WriteLine(r.Szukaj("", "Kraków", DateTime.Now).Blad);
        Console.WriteLine(r.Szukaj("Warszawa", "Warszawa", DateTime.Now).Blad);
        Console.WriteLine(r.Rezerwuj(lot.Wartosc!, 100, 10).Blad);
        Console.WriteLine(r.Rezerwuj(lot.Wartosc!, 1, 999).Blad);
        Console.WriteLine(r.Zaplac(0, "1234567890123456").Blad);
        Console.WriteLine(r.Zaplac(100, "abc").Blad);
    }
}
