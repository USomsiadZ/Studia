/*
Twoim zadaniem jest zaprojektowanie i zaimplementowanie kilku współpracujących ze sobą klas, które reprezentują podstawowe elementy geometrii (punkt, odcinek, trójkąt, prostokąt) oraz obraz, mogący przechowywać wiele figur. Należy zamodelować właściwe relacje kompozycji i agregacji pomiędzy tymi klasami.

Wymagania
Należy zaimplementować klasy reprezentujące:

punkt w przestrzeni 2D,
odcinek złożony z dwóch punktów,
trójkąt złożony z odcinków
kwadrat złożony z odcinków,
obraz / płótno / kolekcję figur, pozwalające przechowywać wiele figur.
Klasy powinny umożliwiać:
tworzenie tych obiektów w poprawnym stanie,
odczyt podstawowych informacji o obiektach,
przesuwanie punktów i figur na płaszczyźnie,
obliczanie długości odcinka,
obliczanie obwodu figur,
dodawanie figur do kolekcji,
wypisywanie informacji o przechowywanych figurach (w sposób naturalny dla danego języka programowania).
Wskazówki
Przemyśl, czy obiekty złożone powinny przyjmować gotowe komponenty, czy raczej tworzyć je samodzielnie na podstawie prostszych danych (np. współrzędnych).
Zwróć uwagę na skutki współdzielenia tych samych obiektów między różnymi obiektami złożonymi.
W klasach złożonych unikaj powielania logiki - jeśli jakaś operacja może być wykonana przez komponent, warto ją tam pozostawić.
Pamiętaj o hermetyzacji.
Rozważ wykorzystanie wspólnej abstrakcji figur do uproszczenia pracy z kolekcją.
*/
// Obraz moze istniej bez żadnych figur
// Aby przesunąć figurę, należy przesunąć wszystkie jej punkty
// Wystarczy jeden punkt aby narysować figurę
// ToString podaczas wypisywania informacji o figurze
// Współdzielenie obiektów między różnymi obiektami złożonymi jest złym pomysłem,bo jak przesuwamy to by się prze, lepiej utworzyć nowy obiekt -> this.ps = new Punkt(ps.x, ps.y)
// W klasach złożonych unikaj powielania logiki - jeśli jakaś operacja może być wykonana przez komponent, warto ją tam pozostawić.
// Pamiętaj o hermetyzacji.
// Rozważ wykorzystanie wspólnej abstrakcji figur do uproszczenia pracy z kolekcją.

using System;
using System.Collections.Generic;

public class Punkt
{
    public int X { get; set; }
    public int Y { get; set; }

    public Punkt(int x, int y)
    {
        X = x;
        Y = y;
    }

    public void Przesun(int dx, int dy)
    {
        X += dx;
        Y += dy;
    }

    public override string ToString() => $"({X}, {Y})";
}

public abstract class Figura
{
    public abstract double Obwod();
    public abstract void Przesun(int dx, int dy);
    public virtual double Pole() => 0;
}

public class Odcinek : Figura
{
    private Punkt a;
    private Punkt b;

    public Odcinek(Punkt a, Punkt b)
    {
        this.a = new Punkt(a.X, a.Y);
        this.b = new Punkt(b.X, b.Y);
    }

    public double Dlugosc()
    {
        double dx = b.X - a.X;
        double dy = b.Y - a.Y;
        return Math.Sqrt(dx * dx + dy * dy);
    }

    public override double Obwod() => Dlugosc();

    public override void Przesun(int dx, int dy)
    {
        a.Przesun(dx, dy);
        b.Przesun(dx, dy);
    }

    public override string ToString() => $"Odcinek {a} -> {b}, długość = {Dlugosc()}";
}

public class Trojkat : Figura
{
    private Odcinek ab;
    private Odcinek bc;
    private Odcinek ca;

    public Trojkat(Punkt a, Punkt b, Punkt c)
    {
        ab = new Odcinek(a, b);
        bc = new Odcinek(b, c);
        ca = new Odcinek(c, a);
    }

    public override double Obwod() => ab.Obwod() + bc.Obwod() + ca.Obwod();

    public override double Pole()
    {
        // Wzór Herona: s = (a+b+c)/2, P = sqrt(s(s-a)(s-b)(s-c))
        double s = Obwod() / 2.0;
        double pole = Math.Sqrt(s * (s - ab.Obwod()) * (s - bc.Obwod()) * (s - ca.Obwod()));
        return pole;
    }

    public override void Przesun(int dx, int dy)
    {
        ab.Przesun(dx, dy);
        bc.Przesun(dx, dy);
        ca.Przesun(dx, dy);
    }

    public override string ToString() => $"Trójkąt: {ab}; {bc}; {ca}; obwód = {Obwod()}; pole = {Pole()}";
}

public class Kwadrat : Figura
{
    private Odcinek dol;
    private Odcinek prawa;
    private Odcinek gora;
    private Odcinek lewa;

    public Kwadrat(Punkt lewyDolny, int bok)
    {
        Punkt ld = new Punkt(lewyDolny.X, lewyDolny.Y);
        Punkt pd = new Punkt(lewyDolny.X + bok, lewyDolny.Y);
        Punkt pg = new Punkt(lewyDolny.X + bok, lewyDolny.Y + bok);
        Punkt lg = new Punkt(lewyDolny.X, lewyDolny.Y + bok);

        dol = new Odcinek(ld, pd);
        prawa = new Odcinek(pd, pg);
        gora = new Odcinek(pg, lg);
        lewa = new Odcinek(lg, ld);
    }

    public override double Obwod() => dol.Obwod() + prawa.Obwod() + gora.Obwod() + lewa.Obwod();

    public override double Pole() => dol.Obwod() * dol.Obwod();

    public override void Przesun(int dx, int dy)
    {
        dol.Przesun(dx, dy);
        prawa.Przesun(dx, dy);
        gora.Przesun(dx, dy);
        lewa.Przesun(dx, dy);
    }

    public override string ToString() => $"Kwadrat: {dol}; {prawa}; {gora}; {lewa}; obwód = {Obwod()}; pole = {Pole()}";
}

public class Obraz
{
    private List<Figura> figury = new List<Figura>();

    public void Dodaj(Figura f)
    {
        figury.Add(f);
    }

    public void Wypisz()
    {
        Console.WriteLine($"Obraz ({figury.Count} figur):");
        foreach (Figura f in figury)
        {
            Console.WriteLine("  " + f.ToString());
        }
    }
}

class Program
{
    static void Main()
    {
        Odcinek od = new Odcinek(new Punkt(0, 0), new Punkt(3, 4));
        Trojkat tr = new Trojkat(new Punkt(0, 0), new Punkt(4, 0), new Punkt(0, 3));
        Kwadrat kw = new Kwadrat(new Punkt(1, 1), 5);

        Obraz obraz = new Obraz();
        obraz.Dodaj(od);
        obraz.Dodaj(tr);
        obraz.Dodaj(kw);

        obraz.Wypisz();

        Console.WriteLine("\nPrzesuwam odcinek o (10, 5):");
        od.Przesun(10, 5);
        obraz.Wypisz();
    }
}
