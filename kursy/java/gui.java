import javax.swing.*;
public class gui {
    public static void main(){
        JFrame gui = new JFrame("Gui");
        gui.setSize(600,600);
        gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gui.setLayout(null);

        JTextField text = new JTextField();
        text.setBounds(20,100,100,50);

        JButton button = new JButton("Button");
        button.setBounds(20, 50, 100, 50);

        JLabel label = new JLabel("test");
        label.setBounds(20, 20 , 100, 50);


        button.addActionListener(e ->{
            String name = text.getText();
            label.setText(name);
        });
        gui.add(button);
        gui.add(label);
        gui.add(text);
        gui.setVisible(true);
    }
}
