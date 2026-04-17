class Osoba
{

    public string imie { get; }

    public Osoba(string imie)
    {
        this.imie = imie;
        Console.WriteLine($"Imie: {imie}");
    }
}

class Student : Osoba
{
    private int indeks;

    public Student(string imie, int indeks)
        : base(imie)   // <- przekazanie imienia do klasy Osoba
    {
        this.indeks = indeks;
        Console.WriteLine($"Indeks: {indeks}");
    }
}

class Program
{
    static void Main()
    {
        Student student = new Student("Jan", 12345);
        //Console.WriteLine(student.imie);
    }
}