import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input N: ");
        int n = 1;

        try {
            n = scanner.nextInt();
        } catch (InputMismatchException e) {
            System.out.println("ERROR");
        }

        RunF3 f3 = new RunF3(n);
        RunF1 f1 = new RunF1(n);
        RunF2 f2 = new RunF2(n);

        try {
            f1.t.join();
            f2.t.join();
            f3.t.join();
        }
        catch (InterruptedException e) {
            System.out.println("Interupted");
        }

        f1.printResult();
        f2.printResult();
        f3.printResult();
    }
}
