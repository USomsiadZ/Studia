/*
Projektujesz prosty system obsługi dokumentów używanych w firmie. W systemie mają występować różne typy dokumentów, np. raporty, notatki służbowe, faktury, umowy.

Poszczególne dokumenty pełnią różne role:

raport służy do przedstawiania informacji na określony temat; może mieć różną objętość i czasem zawiera podsumowanie,
notatka służbowa jest wykorzystywana do komunikacji wewnętrznej; może mieć określony priorytet oraz odbiorcę lub dział,
faktura jest związana z rozliczeniami; powinna umożliwiać np. obliczenie kwoty końcowej oraz sprawdzenie, czy termin płatności już minął,
umowa opisuje ustalenia między stronami; można dla niej określić, czy nadal obowiązuje oraz czy została podpisana.
Niektóre dokumenty służą głównie do przekazywania treści, inne mają bardziej formalny charakter i są związane z obiegiem spraw lub rozliczeniami.

Twoim zadaniem jest zaprojektowanie hierarchii klas z wykorzystaniem dziedziczenia, która odzwierciedli zarówno:

cechy wspólne wszystkich dokumentów,
jak i podobieństwa występujące tylko między niektórymi ich rodzajami.
Wymagania
Hierarchia powinna zawierać:
klasę najbardziej ogólną,
co najmniej jeden poziom klas pośrednich,
klasy szczegółowe reprezentujące konkretne typy dokumentów.
W projekcie należy:
zidentyfikować cechy wspólne dokumentów,
pogrupować podobne dokumenty w szersze kategorie (jeśli ma to sens),
przypisać odpowiednie odpowiedzialności do właściwych klas.
Każda klasa powinna zawierać:
pola opisujące stan obiektu,
konstruktor inicjalizujący wszystkie pola,
metody wynikające z roli danej klasy.
Oprócz operacji charakterystycznych dla konkretnych typów dokumentów, w projekcie powinny pojawić się także operacje wspólne dla wszystkich dokumentów (np. związane z prezentacją podstawowych informacji lub wykorzystaniem danych opisujących dokument).
Klasy powinny różnić się nie tylko danymi, ale również zachowaniem.
Zadbaj o hermetyzację (pola prywatne, dostęp przez metody).
UML
Zaprojektowaną przez siebie hierarchię przedstaw na diagramie UML.

Testy
W programie głównym:

utwórz obiekty wszystkich zaprojektowanych klas,
sprawdź poprawność działania konstruktorów,
przetestuj zarówno operacje wspólne, jak i specyficzne dla poszczególnych typów dokumentów.*/

using System;

namespace OOP.zajecia6
{
    abstract class Dokument
    {
        private string tytul;
        private string autor;
        private int dataUtworzenia;
        private string zawartosc;

        protected Dokument(string tytul, string autor, int dataUtworzenia, string zawartosc)
        {
            this.tytul = tytul;
            this.autor = autor;
            this.dataUtworzenia = dataUtworzenia;
            this.zawartosc = zawartosc;
        }

        public string PobierzTytul() => tytul;
        public string PobierzAutor() => autor;
        public int PobierzDateUtworzenia() => dataUtworzenia;
        public string PobierzZawartosc() => zawartosc;

        public string PokazInfo()
        {
            return $"Tytul: {tytul}, Autor: {autor}, Data: {dataUtworzenia}";
        }

        public abstract string OpisRoli();
    }

    abstract class DokumentTekstowy : Dokument
    {
        private int liczbaSlow;

        protected DokumentTekstowy(string tytul, string autor, int dataUtworzenia, string zawartosc)
            : base(tytul, autor, dataUtworzenia, zawartosc)
        {
            liczbaSlow = PoliczSlowa(zawartosc);
        }

        public int PobierzLiczbeSlow() => liczbaSlow;

        private int PoliczSlowa(string tekst)
        {
            if (string.IsNullOrWhiteSpace(tekst))
            {
                return 0;
            }

            return tekst.Split(' ', StringSplitOptions.RemoveEmptyEntries).Length;
        }
    }

    class Raport : DokumentTekstowy
    {
        private string podsumowanie;

        public Raport(
            string tytul,
            string autor,
            int dataUtworzenia,
            string zawartosc,
            string podsumowanie)
            : base(tytul, autor, dataUtworzenia, zawartosc)
        {
            this.podsumowanie = podsumowanie;
        }

        public string PobierzPodsumowanie() => podsumowanie;
        public bool CzyRaportObszerny(int progSlow) => PobierzLiczbeSlow() > progSlow;
        public override string OpisRoli() => "Raport przedstawia informacje na okreslony temat.";
    }

    class NotatkaSluzbowa : DokumentTekstowy
    {
        private string priorytet;
        private string odbiorcaLubDzial;

        public NotatkaSluzbowa(
            string tytul,
            string autor,
            int dataUtworzenia,
            string zawartosc,
            string priorytet,
            string odbiorcaLubDzial) : base(tytul, autor, dataUtworzenia, zawartosc)
        {
            this.priorytet = priorytet;
            this.odbiorcaLubDzial = odbiorcaLubDzial;
        }

        public string PobierzPriorytet() => priorytet;
        public string PobierzOdbiorceLubDzial() => odbiorcaLubDzial;
        public override string OpisRoli() => "Notatka wspiera komunikacje wewnetrzna.";
    }

    class Faktura : Dokument
    {
        private string numerDokumentu;
        private decimal kwotaNetto;
        private decimal stawkaVat;
        private int terminPlatnosci;

        public Faktura(
            string tytul,
            string autor,
            int dataUtworzenia,
            string zawartosc,
            string numerDokumentu,
            decimal kwotaNetto,
            decimal stawkaVat,
            int terminPlatnosci)
            : base(tytul, autor, dataUtworzenia, zawartosc)
        {
            this.numerDokumentu = numerDokumentu;
            this.kwotaNetto = kwotaNetto;
            this.stawkaVat = stawkaVat;
            this.terminPlatnosci = terminPlatnosci;
        }

        public string PobierzNumerDokumentu() => numerDokumentu;
        public decimal ObliczKwoteKoncowa() => Math.Round(kwotaNetto * (1 + stawkaVat), 2);
        public bool CzyPoTerminie(int dzis) => dzis > terminPlatnosci;
        public override string OpisRoli() => "Faktura sluzy do rozliczen.";
    }

    class Umowa : Dokument
    {
        private string numerDokumentu;
        private int dataOd;
        private int dataDo;
        private bool podpisana;

        public Umowa(
            string tytul,
            string autor,
            int dataUtworzenia,
            string zawartosc,
            string numerDokumentu,
            int dataOd,
            int dataDo,
            bool podpisana)
            : base(tytul, autor, dataUtworzenia, zawartosc)
        {
            this.numerDokumentu = numerDokumentu;
            this.dataOd = dataOd;
            this.dataDo = dataDo;
            this.podpisana = podpisana;
        }

        public string PobierzNumerDokumentu() => numerDokumentu;
        public bool CzyObowiazuje(int dzis) => dzis >= dataOd && dzis <= dataDo;
        public bool CzyPodpisana() => podpisana;
        public override string OpisRoli() => "Umowa opisuje ustalenia miedzy stronami.";
    }

    public class Program
    {
        static void Main()
        {
            Raport raport = new Raport(
                "Raport kwartalny",
                "Anna Kowalska",
                20260401,
                "Sprzedaz wzrosla o dwanascie procent kwartalnie.",
                "Trend jest pozytywny.");

            NotatkaSluzbowa notatka = new NotatkaSluzbowa(
                "Pilna notatka",
                "Piotr Nowak",
                20260403,
                "Prosze o pilna aktualizacje systemu.",
                "Wysoki",
                "Dzial IT");

            Faktura faktura = new Faktura(
                "Faktura FV/04/2026",
                "Biuro rachunkowe",
                20260405,
                "Usluga serwisowa za marzec",
                "FV/04/2026",
                1000m,
                0.23m,
                20260420);

            Umowa umowa = new Umowa(
                "Umowa serwisowa",
                "Dzial prawny",
                20260101,
                "Umowa na utrzymanie infrastruktury.",
                "UM/2026/01",
                20260101,
                20261231,
                true);

            Dokument[] dokumenty = { raport, notatka, faktura, umowa };

            Console.WriteLine("=== Operacje wspolne ===");
            foreach (Dokument dokument in dokumenty)
            {
                Console.WriteLine(dokument.PokazInfo());
                Console.WriteLine(dokument.OpisRoli());
                Console.WriteLine();
            }

            Console.WriteLine("=== Operacje specyficzne ===");
            Console.WriteLine($"Raport obszerny (>5 slow): {raport.CzyRaportObszerny(5)}");
            Console.WriteLine($"Notatka priorytet: {notatka.PobierzPriorytet()}, odbiorca: {notatka.PobierzOdbiorceLubDzial()}");
            Console.WriteLine($"Kwota koncowa faktury: {faktura.ObliczKwoteKoncowa()}");
            Console.WriteLine($"Faktura po terminie (20260425): {faktura.CzyPoTerminie(20260425)}");
            Console.WriteLine($"Umowa obowiazuje (20260701): {umowa.CzyObowiazuje(20260701)}");
            Console.WriteLine($"Umowa podpisana: {umowa.CzyPodpisana()}");
        }
    }
}
