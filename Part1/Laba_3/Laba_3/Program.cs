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

            RunF1 f1 = new RunF1(n);
            RunF3 f3 = new RunF3(n);
            RunF2 f2 = new RunF2(n);
            f1.thread.Join();
            f3.thread.Join();
            f2.thread.Join();
            f1.PrintResult();
            f3.PrintResult();
            f2.PrintResult();
        }
    }
}
