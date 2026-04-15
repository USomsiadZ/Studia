/*
Zaprojektuj i zaimplementuj klasę reprezentującą czas trwania (może być ona używana w systemie do zwracania czasu trwania pewnej operacji lub wydarzenia, np. 45 sekund, 1 minuta 20 sekund, 1 godzina 15 minut). Powinna ona umożliwiać tworzenie obiektów oraz wykonywanie podstawowych operacji na czasie trwania.

Zaprojektuj interfejs publiczny klasy.
Zaproponuj wewnętrzną reprezentację.
Narysuj diagram UML zgodny ze swoją propozycją.
Wykonaj implementację w wybranym obiektowym języku programowania (w rozwiązaniu nie korzystaj z gotowych klas bibliotecznych).
Napisz w funkcji main kilka prostych testów, pokazujących działanie klasy i jej operacji:
tworzenie obiektów na różne sposoby,
dodawanie i odejmowanie dwóch czasów,
porównywanie dwóch czasów,
konwersję na liczbowy format w wybranej jednostce (np. do sprawdzenia długości czasu trwania w minutach),
wypisywanie czytelnej, tekstowej reprezentacji do konsoli (w sposób naturalny dla danego języka programowania).
Zadbaj o to, aby obiekty klasy zawsze reprezentowały poprawny czas trwania, a wszystkie operacje na obiektach zachowywały spójność ich stanu.
Jeśli język na to pozwala, postaraj się wykorzystać możliwość przeciążania operatorów.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Threading.Tasks;

public interface CCzas
{
    public int validacja();
    public void Dodaj(int minuty);
    public void Dodaj(int godziny, int minuty);
    public void Odejmij(int minuty);
    public void Odejmij(int godziny, int minuty);
    public string Wypisz();
}
class Czas : CCzas
{
    private int time = 0;
    public int validacja()
    {
        if (time < 0) time = 0;
        return time;
    }
    public int validacja(int time)
    {
        if (time < 0) return 0;
        return time;
    }

    public void Dodaj(int minuty)
    {
        time += minuty;
    }
    public void Dodaj(int godziny, int minuty)
    {
        Dodaj(minuty);
        Dodaj(godziny * 60);

    }
    public void Odejmij(int minuty)
    {
        time -= minuty;
        validacja();
    }
    public void Odejmij(int godziny, int minuty)
    {
        Odejmij(minuty);
        Odejmij(godziny * 60);
    }
    public string Wypisz()
    {
        int minuty = time % 60;
        if (time < 60) return $"Minuty: {minuty}";
        int godziny = time / 60;
        return $"Godziny: {godziny} Minuty: {minuty}";

    }
    public Czas(int minuty)
    {
        this.time = minuty;
        validacja();
    }
    public Czas(int godziny, int minuty)
    {
        this.time = minuty + godziny * 60;
        validacja();
    }
    public Czas Add(Czas p)
    {
        return new Czas(this.time + p.time);
    }
    public int ToMinutes()
    {
        return this.time;
    }
    public double ToHour()
    {
        return (double)this.time / 60.0;
    }
    public Czas Minus(Czas other)
    {
        Czas p = new Czas(this.time - other.time);
        if (p.time < 0) p.time = 0;
        return p;
    }

    //* Dodatkowe użycie - Przeciążenie operatora
    public static Czas operator +(Czas a, Czas b)
    {
        return new Czas(a.time + b.time);
    }
    public static Czas operator +(Czas a, int b)
    {
        return new Czas(a.time + b);
    }

    public static Czas operator -(Czas a, Czas b)
    {
        Czas p = new Czas(a.time - b.time);
        if (p.time < 0) p.time = 0;
        return p;
    }
    public static bool operator <(Czas a, Czas b)
    {
        return a.time < b.time;
    }
    public static bool operator >(Czas a, Czas b)
    {
        return a.time > b.time;
    }
    //Lambda
    public bool czy_parzysty => this.time % 2 == 0;

    public bool czy_parzyscie2
    {
        get { return this.time % 2 == 0; }
    }





}

namespace OOP.zajecia5
{
    public class Program
    {
        static void Main()
        {
            //czastrw t3 = t1.add(t2)
            Czas t1 = new(60);
            Czas t2 = new(1, 75);
            Console.WriteLine("h" + t2.ToHour());
            Czas t3 = t1.Add(t2);
            Czas t4 = t1 + t2;
            Czas t5 = t1 - t2;
            Console.WriteLine(t1.Wypisz());
            Console.WriteLine(t2.Wypisz());
            Console.WriteLine(t3.Wypisz());
            Console.WriteLine(t4.Wypisz());
            Console.WriteLine(t1 > t2);
            Console.WriteLine(t1 < t2);
            Console.WriteLine(t2.ToMinutes());
            Console.WriteLine(t2.czy_parzysty);
            t2 = t2 + 1;
            Console.WriteLine(t2.czy_parzysty);

        }
    }
}