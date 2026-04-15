# `po-05.pdf` - streszczenie pod C#

## Dziedziczenie (podstawy)
- Dziedziczenie modeluje relację **is-a** (np. `Developer : Employee`).
- Klasa pochodna przejmuje składowe klasy bazowej i może:
  - dodać nowe pola/metody,
  - nadpisać zachowanie.
- W C#: dziedziczenie zapisujemy przez `:`.

```csharp
class Dokument
{
    public string Tytul { get; set; }
    public string Autor { get; set; }

    public Dokument(string tytul, string autor)
    {
        Tytul = tytul;
        Autor = autor;
    }
}

class Raport : Dokument
{
    public string Podsumowanie { get; set; }

    public Raport(string tytul, string autor, string podsumowanie)
        : base(tytul, autor)
    {
        Podsumowanie = podsumowanie;
    }
}
```

## Nadpisywanie vs ukrywanie
- **Nadpisywanie**:
  - baza: `virtual`,
  - pochodna: `override`,
  - działa polimorfizm (wybór metody wg typu rzeczywistego obiektu).
- **Ukrywanie**:
  - pochodna: `new`,
  - brak polimorfizmu dla referencji typu bazowego (decyduje typ referencji).
- Do wywołania implementacji bazowej używa się `base.Method()`.

```csharp
class Osoba
{
    public virtual void PrzedstawSie() => Console.WriteLine("Jestem osoba.");
    public void Przywitaj() => Console.WriteLine("Czesc od Osoba.");
}

class Pracownik : Osoba
{
    public override void PrzedstawSie() => Console.WriteLine("Jestem pracownik.");
    public new void Przywitaj() => Console.WriteLine("Czesc od Pracownik.");
}

Osoba o = new Pracownik();
o.PrzedstawSie(); // Jestem pracownik.
o.Przywitaj();    // Czesc od Osoba.
```

## Konstruktory w dziedziczeniu
- Konstruktory **nie są dziedziczone**.
- Konstruktor pochodny powinien delegować inicjalizację części bazowej przez `: base(...)`.
- Najpierw wykonuje się konstruktor bazowy, potem pochodny.

```csharp
class Dokument
{
    public string Tytul { get; }

    public Dokument(string tytul)
    {
        Tytul = tytul;
    }
}

class Raport : Dokument
{
    public int LiczbaStron { get; }

    public Raport(string tytul, int liczbaStron)
        : base(tytul)
    {
        LiczbaStron = liczbaStron;
    }
}
```

## Hermetyzacja + dziedziczenie
- `private` w bazie nie jest dostępne bezpośrednio w klasie pochodnej.
- `protected` jest dostępne w klasach pochodnych, ale należy używać ostrożnie.
- Dobra praktyka: preferować publiczny interfejs metod (gettery/metody domenowe), zamiast szerokiego wystawiania pól.

## Projektowanie hierarchii
- Dziedziczenie stosować, gdy relacja semantyczna naprawdę jest **"jest rodzajem"**.
- Unikać dziedziczenia tylko dla reużycia kodu.
- Częsty antywzorzec: dziedziczenie przy relacji "ma" (powinno być kompozycją).

---

# `po-06.pdf` - streszczenie pod C#

## Polimorfizm i typy
- Polimorfizm dynamiczny: ta sama referencja bazowa wywołuje różne implementacje (`override`) zależnie od typu obiektu.
- Upcasting (pochodna -> bazowa) jest automatyczny i bezpieczny.
- Downcasting (bazowa -> pochodna) może być niebezpieczny i wymaga sprawdzenia typu.

```csharp
class Zwierze
{
    public virtual string WydajDzwiek() => "???";
}

class Pies : Zwierze
{
    public override string WydajDzwiek() => "Hau hau!";
}

class Kot : Zwierze
{
    public override string WydajDzwiek() => "Miau!";
}

Zwierze[] zwierzeta = { new Pies(), new Kot() };
foreach (var z in zwierzeta)
{
    Console.WriteLine(z.WydajDzwiek());
}
```

## RTTI w C#
- Narzędzia:
  - `is` - sprawdzanie typu,
  - `as` - bezpieczne rzutowanie (`null` zamiast wyjątku),
  - `GetType()` - typ runtime.
- RTTI używać, gdy trzeba; często lepszy projekt to polimorfizm (`virtual/override`) zamiast ręcznego rozgałęziania po typie.

```csharp
class Pracownik { }

class Ksiegowy : Pracownik
{
    public void GenerujRaport() => Console.WriteLine("Raport wygenerowany.");
}

Pracownik p = new Ksiegowy();

if (p is Ksiegowy)
{
    Console.WriteLine("To jest ksiegowy.");
}

Ksiegowy k = p as Ksiegowy;
if (k != null)
{
    k.GenerujRaport();
}
```

## Metody wirtualne w C#
- Domyślnie metody są statycznie wiązane.
- Do polimorfizmu:
  - w bazie `virtual`,
  - w pochodnej `override`.
- `sealed override` blokuje dalsze nadpisywanie tej metody.
- `sealed class` blokuje dziedziczenie po klasie.

## Klasy i metody abstrakcyjne
- `abstract class` - nie można tworzyć instancji.
- `abstract method` - kontrakt bez implementacji, musi być nadpisana w klasie konkretnej.
- Abstrakcja pomaga wymusić spójny interfejs i wspiera polimorfizm.

```csharp
abstract class Figura
{
    public abstract double Pole();
}

class Prostokat : Figura
{
    public double A { get; }
    public double B { get; }

    public Prostokat(double a, double b)
    {
        A = a;
        B = b;
    }

    public override double Pole() => A * B;
}
```

## Interfejsy
- Interfejs definiuje **co** obiekt potrafi, nie **jak**.
- W C# implementacja: `class X : IY`.
- Użyteczne do luźnego sprzężenia, wspólnych kontraktów i pracy na typie interfejsowym.

```csharp
interface IDrukowalny
{
    void Drukuj();
}

class Faktura : IDrukowalny
{
    public void Drukuj() => Console.WriteLine("Drukuje fakture...");
}
```

## Wielodziedziczenie
- C# **nie wspiera** wielodziedziczenia klas (i to upraszcza wiele problemów znanych z C++).
- Wielodziedziczenie zachowań modeluje się interfejsami.

---

# Mini sciaga C# (z obu wykladow)
- Uzywaj `virtual/override`, gdy chcesz polimorfizm.
- Uzywaj `new`, tylko gdy swiadomie chcesz ukryc metode.
- W konstruktorach pochodnych zawsze rozwaz `: base(...)`.
- Projektuj hierarchie tylko dla prawdziwego **is-a**.
- Gdy relacja to "ma" -> preferuj kompozycje.
- Gdy klasy maja wspolne zachowanie-kontrakt, ale rozne implementacje -> interfejs/abstrakcja.
