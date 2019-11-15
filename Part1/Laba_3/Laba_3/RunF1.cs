using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Laba_3
{
    class RunF1
    {
        public Thread thread;
        int n;
        private int[] B;
        private int[] C;
        private int[][] MA;
        private int[][] ME;
        private int[][] MD;

        public RunF1(int n)
        {
            thread = new Thread(this.Run);
            this.n = n;
            Console.WriteLine("F1 started");
            thread.Start();
        }

        void Run()
        {
            B = new int[n];
            C = new int[n];
            MA = new int[n][];
            ME = new int[n][];
            Data.GenerateVector(B);
            Data.GenerateVector(C);
            Data.GenerateMatrix(MA);
            Data.GenerateMatrix(ME);
            MD = Data.F1(B, C, MA, ME);
            Console.WriteLine("F1 finished");
        }

        public void PrintResult()
        {
            Console.WriteLine("\nResult of F1: MD = (B*C)*(MA*ME):\n");
            Data.PrintMatrix(MD);
        }
    }
 }
