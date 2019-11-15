import java.util.Random;
import java.util.concurrent.Semaphore;

public class Data {
    private static Random random = new Random();

    public static void f1(int[] S, int[] T, int[][] MO, int[][] MP, int n) {
        Semaphore firstSemaphore = new Semaphore(1);
        Semaphore secondSemaphore = new Semaphore(1);
        int[][] MOMP = new int[n][n];
        int[] ST = new int[n];

        RunMatrixFirsHalf matrixFirsHalf = new RunMatrixFirsHalf(MO, MP, MOMP, n, firstSemaphore, secondSemaphore);
        RunMatrixSecondHalf matrixSecondHalf = new RunMatrixSecondHalf(MO, MP, MOMP, n, secondSemaphore, firstSemaphore);
        PlusVectors plusVectors = new PlusVectors(S, T, ST, n);

        try {
            matrixFirsHalf.t.join();
            matrixSecondHalf.t.join();
            plusVectors.t.join();
        }
        catch (InterruptedException e) {
            System.out.println("Interupted");
        }

        for (int i = 0; i < n; i++) {
            S[i] = 0;
            for (int j = 0; j < n; j++) {
                S[i] += MOMP[i][j] * ST[j];
            }
        }
    }

    public static void generateVector(int[] vector) {
        for (int i = 0; i < vector.length; i++)
            vector[i] = 1;
    }

    public static void generateMatrix(int[][] matrix) {
        for (int i = 0; i < matrix.length; i++)
            generateVector(matrix[i]);
    }

    public static  void printMatrix(int[][] A) {
        for (int i = 0; i < A.length; i++) {
            for (int j = 0; j < A.length; j++) {
                System.out.print(A[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void printVector(int[] A) {
        for (int i = 0; i < A.length; i++)
            System.out.print(A[i] + " ");
        System.out.println();
    }
}
