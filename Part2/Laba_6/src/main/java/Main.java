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

        int[][] MO = new int[n][n];
        int[][] MP = new int[n][n];
        int[] S = new int[n];
        int[] T = new int[n];

        Data.generateMatrix(MO);
        Data.generateMatrix(MP);
        Data.generateVector(S);
        Data.generateVector(T);

        Data.f1(S, T, MO, MP, n);
        Data.printVector(S);
    }
}
