import java.util.concurrent.Semaphore;

public class RunMatrixFirsHalf implements Runnable {
    private int[][] MO;
    private int[][] MP;
    private int[][] MOMP;
    Thread t;
    int n;
    Semaphore semaphoreRelease;
    Semaphore semaphoreWait;

    public RunMatrixFirsHalf(
        int[][] MO,
        int[][] MP,
        int[][] MOMP,
        int n,
        Semaphore semaphoreRelease,
        Semaphore semaphoreWait) {
            t = new Thread(this, "RunMatrixFirsHalf");
            this.n = n;
            this.MO = MO;
            this.MP = MP;
            this.MOMP = MOMP;
            this.semaphoreRelease = semaphoreRelease;
            this.semaphoreWait = semaphoreWait;

            t.start();
    }

    @Override
    public void run() {
        try {
            semaphoreRelease.acquire();
            int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < k; j++)
                {
                    MOMP[i][j] = 0;
                    for (int r = 0; r < n; r++)
                    {
                        MOMP[i][j] += MO[i][r] * MP[r][j];
                    }
                }
            }

            semaphoreRelease.release();
            semaphoreWait.acquire();
            for (int i = 0; i < k; i++)
            {
                for (int j = k; j < n; j++)
                {
                    MOMP[i][j] = 0;
                    for (int r = 0; r < n; r++)
                    {
                        MOMP[i][j] += MO[i][r] * MP[r][j];
                    }
                }
            }
            semaphoreWait.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
