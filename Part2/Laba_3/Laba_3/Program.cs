using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Laba_3
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Input n:");
            int n = Int32.Parse(Console.ReadLine());

            int[,] MA = new int[n, n];
            int[,] MB = new int[n, n];

            Data.GenerateMatrix(MA, n);
            Data.GenerateMatrix(MB, n);

            int[,] MK = Data.CalcFunc(MA, MB, n);

            Data.PrintMatrix(MK, n);
        }
    }
}
