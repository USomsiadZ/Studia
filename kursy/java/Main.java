import java.util.Scanner;
import java.util.ArrayList;
class Statystyka{
    private int par = 0;
    private int npar = 0;
    void spr(int p){
        if (p % 2 == 0) {
            par++;
        }else{
            npar++;
        }
    }
    void podaj(){
        if(par > npar){
            System.out.println("Parzystych: " +par + " > Nie parzystych: " + npar);
        }else if(npar > par){
            System.out.println("Parzystych: " +par + " < Nie parzystych: " + npar);
        }else{
            System.out.println("Parzystych: " +par + " = Nie parzystych: " + npar);
        }
    }

}
public class Main {
    public static void main() {
        Statystyka stat = new Statystyka();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Podaj słowa:");
        String[] p = new String[64];
        ArrayList<String> worlds = new ArrayList<>();
        String buf = new String();

        while(true){
            buf = scanner.nextLine();
            if(buf.equals("0"))break;
            p = buf.trim().split("\\s+");
            for (int i = 0; i < p.length; i++)
            {
                worlds.add(p[i]);
            }
            
            System.out.println("World count: " + worlds.size());
            stat.spr(worlds.size());
        }
        stat.podaj();

        scanner.close();
    }
}
