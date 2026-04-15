class Osoba
{
    private string imie;

    public Osoba(string imie)
    {
        this.imie = imie;
        Console.WriteLine("Konstruktor Osoba");
    }
}

class Student : Osoba
{
    private int indeks;

    public Student(string imie, int indeks)
        : base(imie)   // <- przekazanie imienia do klasy Osoba
    {
        this.indeks = indeks;
        Console.WriteLine("Konstruktor Student");
    }
}

class Program
{
    static void Main()
    {
        Student student = new Student("Jan", 12345);
    }
}