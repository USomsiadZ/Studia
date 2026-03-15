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
using System.Collections.Generic;
class Program
{
    static void Main()
    {
        string katalog = "/Users/hubert/Github/studia/OOP/zajecia2";
        string sciezkaKlucz = Path.Combine(katalog, "klucz.txt");
        string sciezkaOdpowiedzi = Path.Combine(katalog, "odpowiedzi.txt");
        string sciezkaWyniki = Path.Combine(katalog, "wyniki.txt");

        StreamReader readerKlucz = new(sciezkaKlucz);
        string? liniaKlucz = readerKlucz.ReadLine();
        if (liniaKlucz == null)
        {
            readerKlucz.Close();
            throw new Exception("Nie udało się odczytać klucza");
        }

        StreamReader readerOdpowiedzi = new(sciezkaOdpowiedzi);
        //string[] liniaOdpowiedzi = new string[64];
        List<string> liniaOdpowiedzi = [];


        for (int i = 0; true; i++)
        {
            string? wczytana = readerOdpowiedzi.ReadLine();
            if (wczytana == null) break;
            liniaOdpowiedzi.Add(wczytana);
        }
        if (liniaOdpowiedzi.Count == 0) throw new Exception("Nie udało się wczytać odpowiedzi");

        int poprawne;
        string[] liniaKlucz_tab = liniaKlucz.Trim().Split(" ");
        File.WriteAllText(sciezkaWyniki, "");
        for (int j = 0; j < liniaOdpowiedzi.Count; j++)
        {
            poprawne = 0;
            string[] liniaOdpowiedzi_tab = liniaOdpowiedzi[j].Trim().Split(" ");
            if (liniaOdpowiedzi_tab.Length != liniaKlucz_tab.Length + 2) throw new Exception("Error - dlugosc klucza i odpowiedzi jest różna");
            for (int i = 0; i < liniaKlucz_tab.Length; i++)
            {
                if (liniaKlucz_tab[i] == liniaOdpowiedzi_tab[i + 2]) poprawne++;
                //Console.WriteLine(liniaKlucz_tab[i] + " - " + liniaOdpowiedzi_tab[i + 2]);
            }

            Console.WriteLine(liniaOdpowiedzi_tab[0] + " " + liniaOdpowiedzi_tab[1]);
            Console.WriteLine("Ilość poprawnych: " + poprawne);
            Console.WriteLine("Procent: " + poprawne * 100.0 / liniaKlucz_tab.Length + "%");
            Console.WriteLine("\n");

            int procent = (int)Math.Round(poprawne * 100.0 / liniaKlucz_tab.Length);
            string tekst = $"{liniaOdpowiedzi_tab[0]} {liniaOdpowiedzi_tab[1]} {procent}%";
            File.AppendAllText(sciezkaWyniki, tekst + '\n');
        }




        readerOdpowiedzi.Close();
        readerKlucz.Close();
    }
}