import java.util.Random;

public class Data {
    private static Random random = new Random();

    public static int[][] f1(int[] B, int[] C, int[][] MA, int[][] ME) {
        int vector = vectorMult(B, C);
        int[][] MD = matrixMult(MA, ME);
        MD = matrixMultInt(MD, vector);
        return MD;
    }

    public static int[][] f2(int[][] MH, int[][] MK, int[][] ML) {
        int max = maxMatrix(MH);
        int[][] MG  = matrixMult(MK, ML);
        MG = matrixMultInt(MG, max);
        return MG;
    }

    public static int[] f3(int[][] MP, int[][] MR, int[] T) {
        int[][] matrix = matrixMult(MP, MR);
        int max = maxMatrix(matrix);
        return vectorMultInt(T, max);
    }

    public static void generateVector(int[] vector) {
        for (int i = 0; i < vector.length; i++)
            vector[i] = random.nextInt(5);
    }

    public static void generateMatrix(int[][] matrix) {
        for (int i = 0; i < matrix.length; i++)
            generateVector(matrix[i]);
    }

    public static int[][] matrixMult(int[][] A, int[][] B) {
        int[][] result = new int[A.length][A.length];

        for (int i = 0; i < A.length; i++) {
            for (int j = 0; j < A.length; j++) {
                //result[i][j] = 0;
                for (int r = 0; r < A.length; r++) {
                    result[i][j] += A[i][r] * B[r][j];
                }
            }
        }

        return result;
    }

    public static int vectorMult(int[] A, int[] B) {
        int result = 0;
        for (int i = 0; i < A.length; i++)
            result += A[i] * B[i];
        return  result;
    }

    public static int[] vectorMultInt(int[] A, int a) {
        int[] result = new int[A.length];
        for (int i = 0; i < A.length; i++)
            result[i] += A[i] * a;
        return result;
    }

    public static int[][] matrixMultInt(int[][] A, int a) {
        int[][] result = new int[A.length][A.length];
        for (int i = 0; i < A.length; i++)
            result[i] = vectorMultInt(A[i], a);
        return result;
    }

    public static int maxVector(int[] A) {
        int max = A[0];

        for (int i = 1; i < A.length; i++) {
            if (max < A[i])
                max = A[i];
        }
        return max;
    }

    public static int maxMatrix(int[][] A) {
        int max = A[0][0];

        for(int i = 0; i < A.length; i++) {
            for (int j = 0; j < A.length; j++) {
                if (max < A[i][j])
                    max = A[i][j];
            }
        }

        return  max;
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
