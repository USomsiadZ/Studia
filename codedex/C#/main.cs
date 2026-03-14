using System;


namespace main
{
    class Program
    {
        static void Metoda(string pr = "test", string pr2 = "2")
        {
            Console.WriteLine(pr + pr2);
        }
        static void Metoda(string pr = "test", int pr2 = 2)
        {
            Console.WriteLine(pr + pr2);
        }

        static void Main()
        {
            Metoda(pr2: "3");
            Metoda(pr2: 3);

        }
    }
}