# Zajecia 9 - wyjasnienie nowych rzeczy

Ten plik tlumaczy elementy, ktore pojawily sie w `Program.cs` i moga byc nowe.

## 1) Kolekcje uzyte w zadaniu

### `HashSet<string> uzytkownicy`
- trzyma unikalne loginy,
- szybkie sprawdzanie `Contains`.

### `Dictionary<string, List<string>> skrzynki`
- klucz: login uzytkownika,
- wartosc: lista wiadomosci tego uzytkownika.

To bardzo prosty model "skrzynki odbiorczej": login -> lista tekstow.

## 2) `string? aktywnyLogin`

`aktywnyLogin` ma typ `string?`, czyli moze byc:
- tekstem (ktos zalogowany),
- `null` (nikt nie jest zalogowany).

Dzieki temu latwo sprawdzic stan sesji:
- `aktywnyLogin == null` -> brak sesji.

## 3) `#nullable enable`

Ta dyrektywa wlacza adnotacje nullowalnosci w pliku.
Bez niej `string?` potrafi dawac ostrzezenie kompilatora, jesli projekt nie ma wlaczonego nullable w `.csproj`.

## 4) Dlaczego wiadomosci znikaja po odczycie

Wymaganie, ktore ustaliles:
- po odebraniu wiadomosci maja byc usuniete.

Dlatego `OdbierzNieprzeczytane()`:
1. pobiera aktualna liste,
2. podmienia skrzynke uzytkownika na nowa pusta liste,
3. zwraca pobrana liste.

## 5) `private` vs `protected`

To modyfikatory dostepu - okreslaja, kto moze widziec pole/metode.

### `private`
- dostep tylko wewnatrz tej samej klasy.
- klasy dziedziczace **nie maja** dostepu.

Stosuj, gdy element ma byc ukryty przed calym swiatem poza dana klasa.

### `protected`
- dostep wewnatrz klasy bazowej **i** w klasach pochodnych.
- kod spoza tej hierarchii nadal nie ma dostepu.

Stosuj, gdy chcesz, aby klasy potomne mogly korzystac z danego elementu.

## 6) Krotki przyklad roznicy

```csharp
public class A
{
    private int x = 1;     // tylko A
    protected int y = 2;   // A + klasy dziedziczace
}

public class B : A
{
    public int Test()
    {
        // return x; // blad: x jest private w A
        return y;    // OK: y jest protected
    }
}
```

## 7) Co jest najwazniejsze na zaliczenie tego zadania

- Komunikator obsluguje rejestracje, logowanie, wylogowanie, wysylanie i odbior.
- `Main` testuje scenariusz poprawny i bledne przypadki.
- Uzyte sa sensowne kolekcje (`HashSet`, `Dictionary`, `List`).
- Jeden zalogowany uzytkownik naraz.
- Odbior nieprzeczytanych usuwa je ze skrzynki.
