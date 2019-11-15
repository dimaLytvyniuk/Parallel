public class PlusVectors implements Runnable {
    private int[] S;
    private int[] T;
    private int[] ST;
    Thread t;
    int n;

    public PlusVectors(int[] S, int[] T, int[] ST, int n) {
        t = new Thread(this, "F1");
        this.n = n;
        this.S = S;
        this.T = T;
        this.ST = ST;

        t.start();
    }

    @Override
    public void run() {
        for (int i = 0; i < n; i++)
            ST[i] = S[i] + T[i];
    }
}
