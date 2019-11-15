public class RunF1 implements Runnable {
    private int[] B;
    private int[] C;
    private int[][] MA;
    private int[][] ME;
    private int[][] MD;
    Thread t;
    int n;

    public RunF1(int n) {
        t = new Thread(this, "F1");
        this.n = n;
        System.out.println("F1 started");
        t.start();
    }

    @Override
    public void run() {
        B = new int[n];
        C = new int[n];
        MA = new int[n][n];
        ME = new int[n][n];
        Data.generateVector(B);
        Data.generateVector(C);
        Data.generateMatrix(MA);
        Data.generateMatrix(ME);
        MD = Data.f1(B, C, MA, ME);
        System.out.println("F1 finished");
    }

    public void printResult() {
        System.out.println("\nResult of F1: MD = (B*C)*(MA*ME):\n");
        Data.printMatrix(MD);
    }
}
