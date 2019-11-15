using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
namespace Laba_3
{
    class RunF2
    {
        public Thread thread;
        int n;
        private int[][] MH;
        private int[][] MK;
        private int[][] ML;
        private int[][] MG;

        public RunF2(int n)
        {
            thread = new Thread(this.Run);
            this.n = n;
            Console.WriteLine("F2 started");
            thread.Priority = ThreadPriority.Highest;
            thread.Start();
        }

        void Run()
        {
            MH = new int[n][];
            MK = new int[n][];
            ML = new int[n][];
            Data.GenerateMatrix(MH);
            Data.GenerateMatrix(MK);
            Data.GenerateMatrix(ML);
            MG = Data.F2(MH, MK, ML);
            Console.WriteLine("F2 finished");
        }

        public void PrintResult()
        {
            Console.WriteLine("\nResult of F2: MG = MAX(MH) * (MK*ML):\n");
            Data.PrintMatrix(MG);
        }
    }
}
