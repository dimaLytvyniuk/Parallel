public class RunF2 implements Runnable {
    private int[][] MH;
    private int[][] MK;
    private int[][] ML;
    private int[][] MG;
    Thread t;
    int n;

    public RunF2(int n) {
        t = new Thread(this, "F2");
        this.n = n;
        System.out.println("F2 started");
        t.setPriority(10);
        t.start();
    }
    @Override
    public void run() {
        MH = new int[n][n];
        MK = new int[n][n];
        ML = new int[n][n];
        Data.generateMatrix(MH);
        Data.generateMatrix(MK);
        Data.generateMatrix(ML);
        MG = Data.f2(MH, MK, ML);
        System.out.println("F2 finished");
    }

    public void printResult() {
        System.out.println("\nResult of F2: MG = MAX(MH) * (MK*ML):\n");
        Data.printMatrix(MG);
    }
}
