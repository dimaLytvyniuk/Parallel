using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Laba_3
{
    class Data
    {
        private static Random random = new Random();

        private static Mutex firstMutex = new Mutex();
        private static Mutex secondMutex = new Mutex();

        public static int[,] CalcFunc(int[,] MA, int[,] MB, int n)
        {
            int[,] TMA = new int[n, n];
            int[,] MAMB = new int[n, n];
            int[,] TMAMB = new int[n, n];
            int[,] TMATMAMB = new int[n, n];
            int[,] MK = new int[n, n];

            var tasksMBMA = new Task[]
            {
                new Task(() => MultMBMAFirst(MB, MA, MAMB, n, firstMutex, secondMutex)),
                new Task(() => MultMBMASecond(MB, MA, MAMB, n, secondMutex, firstMutex))
            };
            foreach (var task in tasksMBMA)
            {
                task.Start();
            }

            var taskTMA = Task.Run(() => TransMatrix(MA, TMA, n));

            Task.WaitAll(tasksMBMA);
            var taskTMAMB = Task.Run(() => TransMatrix(MAMB, TMAMB, n));

            taskTMA.Wait();
            taskTMAMB.Wait();

            var tasksTMATMBMA = new Task[]
            {
                new Task(() => MultMBMAFirst(TMA, MAMB, TMATMAMB, n, firstMutex, secondMutex)),
                new Task(() => MultMBMASecond(TMA, MAMB, TMATMAMB, n, secondMutex, firstMutex))
            };
            foreach (var task in tasksTMATMBMA)
            {
                task.Start();
            }
            Task.WaitAll(tasksTMATMBMA);

            var tasksPlusTMATMBMA = new Task[]
            {
                new Task(() => PlusMatrix(TMATMAMB, MA, MK, n, 0, n / 2)), 
                new Task(() => PlusMatrix(TMATMAMB, MA, MK, n, n / 2, n))
            };
            foreach (var task in tasksPlusTMATMBMA)
            {
                task.Start();
            }
            Task.WaitAll(tasksPlusTMATMBMA);

            return MK;
        }

        private static void MultMBMAFirst(int[,] MB, int[,] MA, int[,] MBMA, int n, Mutex releaseMutex, Mutex waitMutex)
        {
            releaseMutex.WaitOne();
            int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);
            for (var i = 0; i < k; i++)
            {
                for (var j = 0; j < k; j++)
                {
                    MBMA[i, j] = 0;
                    for (var r = 0; r < n; r++)
                    {
                        MBMA[i, j] += MB[i, r] * MA[r, j];
                    }
                }
            }
            releaseMutex.ReleaseMutex();
            waitMutex.WaitOne();

            for (var i = 0; i < k; i++)
            {
                for (var j = k; j < n; j++)
                {
                    MBMA[i, j] = 0;
                    for (var r = 0; r < n; r++)
                    {
                        MBMA[i, j] += MB[i, r] * MA[r, j];
                    }
                }
            }
            waitMutex.ReleaseMutex();
        }

        private static void MultMBMASecond(int[,] MB, int[,] MA, int[,] MBMA, int n, Mutex releaseMutex, Mutex waitMutex)
        {
            releaseMutex.WaitOne();
            int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);
            for (var i = k; i < n; i++)
            {
                for (var j = k; j < n; j++)
                {
                    MBMA[i, j] = 0;
                    for (var r = 0; r < n; r++)
                    {
                        MBMA[i, j] += MB[i, r] * MA[r, j];
                    }
                }
            }
            releaseMutex.ReleaseMutex();
            waitMutex.WaitOne();

            for (var i = k; i < n; i++)
            {
                for (var j = 0; j < k; j++)
                {
                    MBMA[i, j] = 0;
                    for (var r = 0; r < n; r++)
                    {
                        MBMA[i, j] += MB[i, r] * MA[r, j];
                    }
                }
            }
            waitMutex.ReleaseMutex();
        }

        public static void PlusMatrix(int[,] MA, int[,] MB, int[,] MK, int n, int start, int end)
        {
            for (int i = start; i < end; i++)
                for (int j = 0; j < n; j++)
                    MK[i, j] = MA[i, j] + MB[i, j];
        }

        public static void TransMatrix(int[,] MA, int[,] TMA, int n)
        {
            Array.Copy(MA, TMA, MA.Length);
            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    TMA[i, j] = MA[j, i];
                    TMA[j, i] = MA[i, j];
                }
            }
        }

        public static void GenerateMatrix(int[,] matrix, int n)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    matrix[i, j] = 1;
        }

        public static void PrintMatrix(int[,] A, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write(A[i,j] + " ");
                }
                Console.WriteLine();
            }
        }
    }
}
