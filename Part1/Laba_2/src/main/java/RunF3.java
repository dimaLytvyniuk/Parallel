public class RunF3 implements Runnable {
    private int[] O;
    private int[] T;
    private int[][] MP;
    private int[][] MR;
    Thread t;
    int n;

    public RunF3(int n) {
        t = new Thread(this, "F1");
        this.n = n;
        System.out.println("F3 started");
        t.setPriority(1);
        t.start();
    }

    @Override
    public void run() {
        T = new int[n];
        MP = new int[n][n];
        MR = new int[n][n];
        Data.generateVector(T);
        Data.generateMatrix(MP);
        Data.generateMatrix(MR);
        O = Data.f3(MP, MR, T);
        System.out.println("F3 finished");
    }

    public void printResult() {
        System.out.println("\nResult of F3: O = MAX(MP*MR) * T:\n");
        Data.printVector(O);
    }
}
