class Student{
    private String imie;
    Student(String imie){
        this.imie = imie;
    }
    void print(){
        System.out.println(imie);
    }
}

public class klasy{
    
    public static void main(){
        Student student = new Student("Marek");
        student.print();
    }
}