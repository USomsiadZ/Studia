#nullable enable
using System;
using System.Collections.Generic;

public class Wiadomosc
{
    public string Tresc { get; }
    public DateTime Data { get; }

    public Wiadomosc(string tresc)
    {
        Tresc = tresc;
        Data = DateTime.Now;
    }

    public override string ToString() => $"[{Data:yyyy-MM-dd HH:mm}] {Tresc}";
}

public class Komunikator
{
    private HashSet<string> uzytkownicy = new HashSet<string>();
    private Dictionary<string, List<Wiadomosc>> skrzynki = new Dictionary<string, List<Wiadomosc>>();
    private string? aktywnyLogin = null;

    public void Zarejestruj(string login)
    {
        uzytkownicy.Add(login);
        if (!skrzynki.ContainsKey(login))
            skrzynki[login] = new List<Wiadomosc>();
    }

    public void Zaloguj(string login)
    {
        aktywnyLogin = login;
    }

    public void Wyloguj()
    {
        aktywnyLogin = null;
    }

    public void Wyslij(string odbiorca, string tresc)
    {
        skrzynki[odbiorca].Add(new Wiadomosc(tresc));
    }

    public List<Wiadomosc> OdbierzNieprzeczytane()
    {
        List<Wiadomosc> wiadomosci = skrzynki[aktywnyLogin!];
        skrzynki[aktywnyLogin!] = new List<Wiadomosc>();
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

        Console.WriteLine("\nProgram zakończył działanie poprawnie.");
    }
}
