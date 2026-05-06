using System.Collections.Generic;
var slownik = new Dictionary<string, List<string>>();
slownik.Add("key1", new());
slownik["key1"].Add("test");
foreach (string slowo in slownik["key1"])
{
    Console.WriteLine(slowo);
}