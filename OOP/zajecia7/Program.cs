namespace OOP.zajecia7
{
    class Zegar
    {
        public int Godzina { get; private set; }
        public int Minuta { get; private set; }
        public int Sekunda { get; private set; }

        public Zegar(int godzina, int minuta, int sekunda)
        {
            if (godzina < 0 || godzina > 23) throw new Exception("Zła godzina");
            if (minuta < 0 || minuta > 59) throw new Exception("Zła minuta");
            if (sekunda < 0 || sekunda > 59) throw new Exception("Zła sekunda");
            Godzina = godzina;
            Minuta = minuta;
            Sekunda = sekunda;
        }

        public virtual void Tik(int sekundy)
        {
            int suma = Godzina * 3600 + Minuta * 60 + Sekunda + sekundy;
            suma = ((suma % 86400) + 86400) % 86400;
            Godzina = suma / 3600;
            Minuta = (suma % 3600) / 60;
            Sekunda = suma % 60;
        }

        public virtual string Opis()
        {
            return $"{Godzina:D2}:{Minuta:D2}:{Sekunda:D2}";
        }
    }

    class ZegarNiedokladny : Zegar
    {
        private int mnoznik;

        public ZegarNiedokladny(int mnoznik, int godzina, int minuta, int sekunda)
            : base(godzina, minuta, sekunda)
        {
            if (mnoznik <= 0) throw new Exception("Mnożnik musi być > 0");
            this.mnoznik = mnoznik;
        }

        public override void Tik(int sekundy)
        {
            base.Tik(sekundy * mnoznik);
        }

        public override string Opis()
        {
            return base.Opis() + $"  [niedokladny x{mnoznik}]";
        }
    }

    class ZegarZAlarmem : Zegar
    {
        private int alarmGodzina;
        private int alarmMinuta;
        private bool alarmZadzwonil;

        public ZegarZAlarmem(int alarmGodzina, int alarmMinuta,
                             int godzina, int minuta, int sekunda)
            : base(godzina, minuta, sekunda)
        {
            this.alarmGodzina = alarmGodzina;
            this.alarmMinuta = alarmMinuta;
        }

        public override void Tik(int sekundy)
        {
            base.Tik(sekundy);
            if (!alarmZadzwonil && Godzina == alarmGodzina && Minuta == alarmMinuta)
            {
                Console.WriteLine(">>> DZWONI ALARM! <<<");
                alarmZadzwonil = true;
            }
        }

        public override string Opis()
        {
            string stan = alarmZadzwonil ? "po alarmie" : "czeka";
            return base.Opis() + $"  [alarm {alarmGodzina:D2}:{alarmMinuta:D2} - {stan}]";
        }
    }

    class ZegarWsteczny : Zegar
    {
        public ZegarWsteczny(int godzina, int minuta, int sekunda)
            : base(godzina, minuta, sekunda) { }

        public override void Tik(int sekundy)
        {
            base.Tik(-sekundy);
        }

        public override string Opis()
        {
            return base.Opis() + "  [wsteczny]";
        }
    }

    public class Program
    {
        static void Main()
        {
            List<Zegar> zegary = new List<Zegar>();
            zegary.Add(new Zegar(12, 0, 0));
            zegary.Add(new ZegarNiedokladny(2, 12, 0, 0));
            zegary.Add(new ZegarZAlarmem(12, 0, 11, 59, 58));
            zegary.Add(new ZegarWsteczny(12, 0, 0));

            Console.WriteLine("--- stan poczatkowy ---");
            foreach (Zegar z in zegary)
                Console.WriteLine(z.Opis());

            for (int krok = 1; krok <= 5; krok++)
            {
                Console.WriteLine($"\n--- krok {krok} ---");
                foreach (Zegar z in zegary)
                {
                    z.Tik(1);
                    Console.WriteLine(z.Opis());
                }
            }
        }
    }
}
