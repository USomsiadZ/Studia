/*
Wczytać klucz odpowiedzi.
Wczytać odpowiedzi uczestników.
Obliczyć procent poprawnych odpowiedzi dla każdej osoby.
Zapisać wyniki do nowego pliku (wyniki.txt) w formacie:
StreamReader readerKlucz = new StreamReader("klucz.txt");
string liniaKlucz = readerKlucz.ReadLine();
readerKlucz.Close();
*/

#nullable enable
using System.IO;
class Program
{
    static void Main()
    {
        StreamReader readerKlucz = new("/Users/hubert/Github/studia/OOP/zajecia2/klucz.txt");
        string? liniaKlucz = readerKlucz.ReadLine() ?? throw new Exception("Nie udało się odczytać klucza");

        StreamReader readerOdpowiedzi = new("/Users/hubert/Github/studia/OOP/zajecia2/odpowiedzi.txt");
        string[] liniaOdpowiedzi = new string[64];

        int dlugosc = 0;
        for (int i = 0; true; i++)
        {
            string? wczytana = readerOdpowiedzi.ReadLine();
            if (wczytana == null) break;
            liniaOdpowiedzi[i] = wczytana;
            dlugosc++;
        }
        if (liniaOdpowiedzi[0] == null) throw new Exception("Nie udało się wczytać odpowiedzi");
        int poprawne;
        string[] liniaKlucz_tab = liniaKlucz.Trim().Split(" ");
        string sciezkaWyniki = "/Users/hubert/Github/studia/OOP/zajecia2/wyniki.txt";
        File.WriteAllText(sciezkaWyniki, "");
        for (int j = 0; j < dlugosc; j++)
        {
            poprawne = 0;
            string[] liniaOdpowiedzi_tab = liniaOdpowiedzi[j].Trim().Split(" ");

            for (int i = 0; i < liniaKlucz_tab.Length; i++)
            {
                if (liniaKlucz_tab[i] == liniaOdpowiedzi_tab[i + 2]) poprawne++;
                //Console.WriteLine(liniaKlucz_tab[i] + " - " + liniaOdpowiedzi_tab[i + 2]);
            }

            Console.WriteLine(liniaOdpowiedzi_tab[0] + " " + liniaOdpowiedzi_tab[1]);
            Console.WriteLine("Ilość poprawnych: " + poprawne);
            Console.WriteLine("Procent: " + poprawne * 10 + "%");
            Console.WriteLine("\n");

            string tekst = liniaOdpowiedzi_tab[0] + " " + liniaOdpowiedzi_tab[1] + "\n" + "Ilość poprawnych: " + poprawne + "\n" + "Procent: " + (poprawne * 10) + "%";
            File.AppendAllText(sciezkaWyniki, tekst + "\n");
        }




        readerOdpowiedzi.Close();
        readerKlucz.Close();
    }
}