namespace main
{
    class Rob()
    {
        private string name = "0";
        public string Name
        {
            get { return "liczba: " + name; }
            set { name = value; }
        }


    }
    class Program
    {
        static void Main()
        {
            Rob p = new()
            {
                Name = "1"
            };
            Console.WriteLine(p.Name);

        }
    }
}