/*
Twoim zadaniem jest zaprojektowanie i zaimplementowanie prostego systemu komunikatora umożliwiającego wymianę wiadomości między użytkownikami.

System powinien umożliwiać:

rejestrowanie użytkowników,
zarządzanie sesją (logowanie i wylogowanie),
wysyłanie wiadomości między użytkownikami,
odbieranie wiadomości.
System powinien poprawnie reagować na sytuacje błędne (np. operacje na nieistniejących użytkownikach, niepoprawne dane, nieprawidłowy stan systemu - uwzględnij zarówno niepoprawne dane wejściowe, jak i operacje niedozwolone w aktualnym stanie systemu). Wykorzystaj w tym celu mechanizm wyjątków.

Wskazówki do implementacji
Klasa komunikatora może odpowiadać za przechowywanie listy zarejestrowanych użytkowników oraz wszystkich przesłanych wiadomości (skorzystaj z klas kolekcji z biblioteki standardowej).
Możesz przyjąć, że w danym momencie zalogowany może być tylko jeden użytkownik, a operacje wysyłania i odbierania wiadomości dotyczą właśnie jego
Wystarczy udostępnić prosty interfejs odczytu wiadomości - np. odebranie wszystkich nieprzeczytanych.
Uwaga: nie obsługuj wyjątków w metodach komunikatora! Operacje powinny jedynie rzucać wyjątki, ich obsługą (złapaniem) zajmie się klient (czyli program główny Main()).
W kodzie Main() przetestuj zarówno scenariusz, gdzie operacje są prawidłowe, jak i próby wykonania błędnych działań, np. wysyłanie wiadomości bez logowania, wysyłanie wiadomości do nieistniejącego użytkownika, itp. Wyjątki nie powinny kończyć działania programu!
UML
Przed implementacją przygotuj diagram UML przedstawiający zaprojektowane klasy i ich relacje (w tym klasy wyjątków).
*/
//Pewien zbior danych który przechowuje: loginy
// zaloguj -> ustaw na aktywny, wyloguj -> null
// wyslij ( login,napis )
// dodac wpis ze zostala wyslana wiadomosc
// w c# zbiór ↑ loginy - hashset
// Struktura - słownik (login - lista wiadomości) dictionary
// Bezsensowna operacja -> wyrzuca wyjątek
// wyjątki: dodanie uzytkownika same nazwie, loginy bez spacji, tylko jeden moze byc zalogowany, wiadomosc musi byc wyslada do uzytkownika ktory istnieje,
// klasy wyjatkow dla kazdego przypadku exception
// jesli widomosc odczytana to wiadomosc kasujemy

#nullable enable
using System;
using System.Collections.Generic;

// ----Wyjątki----
public abstract class Kom : Exception
{
    protected Kom(string message) : base(message) { }
}

public class ZlyLogin : Kom
{
    public ZlyLogin(string login)
        : base($"Nieprawidłowy login: '{login}' (login musi być niepusty i bez spacji).") { }
}

public class LoginZajety : Kom
{
    public LoginZajety(string login)
        : base($"Użytkownik '{login}' już istnieje.") { }
}

public class BrakLoginu : Kom
{
    public BrakLoginu(string login)
        : base($"Użytkownik '{login}' nie istnieje.") { }
}

public class JuzZalogowany : Kom
{
    public JuzZalogowany(string login)
        : base($"Inny użytkownik '{login}' jest już zalogowany.") { }
}

public class BrakSesji : Kom
{
    public BrakSesji()
        : base("Operacja wymaga zalogowanego użytkownika.") { }
}

public class Wiadomosc
{
    public string tresc { get; }
    public DateTime data { get; }

    public Wiadomosc(string tresc)
    {
        this.tresc = tresc;
        data = DateTime.Now;
    }

    public override string ToString() => $"[{data:yyyy-MM-dd HH:mm}] {tresc}";
}

// ----Komunikator----
public class Komunikator
{
    private HashSet<string> uzytkownicy = new HashSet<string>();
    private Dictionary<string, List<Wiadomosc>> skrzynki = new Dictionary<string, List<Wiadomosc>>();
    private string? aktywnyLogin = null;

    public void Zarejestruj(string login)
    {
        if (string.IsNullOrEmpty(login) || login.Contains(' '))
            throw new ZlyLogin(login);
        if (uzytkownicy.Contains(login))
            throw new LoginZajety(login);

        uzytkownicy.Add(login);
        skrzynki[login] = new List<Wiadomosc>();
    }

    public void Zaloguj(string login)
    {
        if (aktywnyLogin != null)
            throw new JuzZalogowany(aktywnyLogin);
        if (!uzytkownicy.Contains(login))
            throw new BrakLoginu(login);

        aktywnyLogin = login;
    }

    public void Wyloguj()
    {
        if (aktywnyLogin == null)
            throw new BrakSesji();

        aktywnyLogin = null;
    }

    public void Wyslij(string odbiorca, string tresc)
    {
        if (aktywnyLogin == null)
            throw new BrakSesji();
        if (!uzytkownicy.Contains(odbiorca))
            throw new BrakLoginu(odbiorca);

        skrzynki[odbiorca].Add(new Wiadomosc(tresc));
    }

    public List<Wiadomosc> OdbierzNieprzeczytane()
    {
        if (aktywnyLogin == null)
            throw new BrakSesji();

        List<Wiadomosc> wiadomosci = skrzynki[aktywnyLogin];
        skrzynki[aktywnyLogin] = new List<Wiadomosc>();
        return wiadomosci;
    }
}

class Program
{
    static void Main()
    {
        Komunikator k = new Komunikator();

        k.Zarejestruj("jan");
        k.Zarejestruj("anna");
        k.Zarejestruj("piotr");

        k.Zaloguj("jan");
        k.Wyslij("anna", "Cześć Anno");
        k.Wyslij("anna", "Spotkamy się jutro");
        k.Wyslij("piotr", "Hej Piotr");
        k.Wyloguj();

        k.Zaloguj("anna");
        Console.WriteLine("----------");
        foreach (Wiadomosc w in k.OdbierzNieprzeczytane())
            Console.WriteLine("  " + w);
        Console.WriteLine("----------");
        k.Wyloguj();

        try { k.Zarejestruj("jan"); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Zarejestruj("nowy user"); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Zarejestruj(""); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Zaloguj("kasia"); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Wyslij("anna", "Hej"); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Wyloguj(); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.OdbierzNieprzeczytane(); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Zaloguj("jan"); k.Zaloguj("anna"); } catch (Kom blad) { Console.WriteLine(blad.Message); }
        try { k.Wyslij("kasia", "Hej"); } catch (Kom blad) { Console.WriteLine(blad.Message); }

        Console.WriteLine("\nProgram zakończył działanie poprawnie.");
    }
}
