/*
Zaprojektuj klasę reprezentującą wizytówkę osoby. Powinna ona umożliwiać:

Skróconą prezentację danych (tylko najważniejsze informacje w prostym formacie).
Pełną prezentację (dane w czytelnej postaci, z podziałem na sekcje).
Brakujące dane powinny być pomijane (np. nie wyświetlamy pustej linii, jeśli dana osoba nie podała numeru telefonu).
Przykładowe wyjście programu:
Skrócona wizytówka dla osoby z pełnymi danymi:
Jan Kowalski (Senior Developer at TechCorp Solutions)
Pełna wizytówka dla osoby z niepełnymi danymi:
============================
Anna Lis
----------------------------
Manager
----------------------------
E-mail: anna.lis@company.com
============================
Kod testowy (main)
W funkcji main() przetestuj poprawność swego rozwiązania:

Stwórz kilka obiektów reprezentujących różne osoby, podając pełne lub niepełne dane, a następnie wyświetl obie wersje wizytówki każdej z nich.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOP.zajecia3
{
    public class Wizytowka
    {
        private string Imie;
        private string Nazwisko;
        private string Stanowisko;
        private string Firma;
        private string Email;
        private string Telefon;
        public Wizytowka(string imie = "", string nazwisko = "", string stanowisko = "", string firma = "", string email = "", string telefon = "")
        {
            this.Imie = imie;
            this.Nazwisko = nazwisko;
            this.Stanowisko = stanowisko;
            this.Firma = firma;
            this.Email = email;
            this.Telefon = telefon;
        }
        public void Pel_wizytowka()
        {
            Console.WriteLine("============================");
            if (!string.IsNullOrWhiteSpace(Imie)) Console.WriteLine($"Imię: {Imie}");
            if (!string.IsNullOrWhiteSpace(Nazwisko)) Console.WriteLine($"Nazwisko: {Nazwisko}");
            if (!string.IsNullOrWhiteSpace(Stanowisko) || !string.IsNullOrWhiteSpace(Firma)) Console.WriteLine("----------------------------");
            if (!string.IsNullOrWhiteSpace(Stanowisko)) Console.WriteLine($"Stanowisko: {Stanowisko}");
            if (!string.IsNullOrWhiteSpace(Firma)) Console.WriteLine($"Firma: {Firma}");
            if (!string.IsNullOrWhiteSpace(Email) || !string.IsNullOrWhiteSpace(Telefon)) Console.WriteLine("----------------------------");
            if (!string.IsNullOrWhiteSpace(Email)) Console.WriteLine($"Email: {Email}");
            if (!string.IsNullOrWhiteSpace(Telefon)) Console.WriteLine($"Telefon: {Telefon}");
            Console.WriteLine("============================");
            Console.WriteLine("\n");
        }
        public void Skrocona_wizytowka()
        {
            Console.WriteLine($"{Nazwisko} {Imie} {Stanowisko} {Firma} {Email} {Telefon}");
            Console.WriteLine("\n");
        }
    }
    public class Program
    {
        static void Main()
        {
            Wizytowka jan = new Wizytowka("Jan", "Kowalski", "Programista", "", "jan.kowalski@gmail.com", "1234567890");
            Wizytowka marek = new Wizytowka("Marek", "", "", "", "marek.nowak@gmail.com", "0987654321");
            Wizytowka adam = new Wizytowka("Adam", "Kowalski", "", "Google", "", "1234567890");
            Wizytowka anna = new Wizytowka("Anna", "Nowak", "Programista", "Facebook", "anna.nowak@gmail.com", "0987654321");
            Wizytowka bartek = new Wizytowka("Bartek", "Kowalski", "", "Google", "bartek.kowalski@gmail.com", "1234567890");
            jan.Pel_wizytowka();
            //jan.Skrocona_wizytowka();
            marek.Pel_wizytowka();
            //marek.Skrocona_wizytowka();

        }
    }
}