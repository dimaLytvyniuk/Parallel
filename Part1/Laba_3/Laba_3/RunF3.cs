using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Laba_3
{
    class RunF3
    {
        public Thread thread;
        int n;
        private int[] O;
        private int[] T;
        private int[][] MP;
        private int[][] MR;

        public RunF3(int n)
        {
            thread = new Thread(this.Run);
            this.n = n;
            thread.Priority = ThreadPriority.Lowest;
            Console.WriteLine("F3 started");
            thread.Start();
        }

        void Run()
        {
            T = new int[n];
            MP = new int[n][];
            MR = new int[n][];
            Data.GenerateVector(T);
            Data.GenerateMatrix(MP);
            Data.GenerateMatrix(MR);
            O = Data.F3(MP, MR, T);
            Console.WriteLine("F3 finished");
        }

        public void PrintResult()
        {
            Console.WriteLine("\nRResult of F3: O = MAX(MP*MR) * T:\n");
            Data.PrintVector(O);
        }
    }
}
