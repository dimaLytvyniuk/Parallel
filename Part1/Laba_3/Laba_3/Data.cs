using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba_3
{
    class Data
    {
        private static Random random = new Random();

        public static int[][] F1(int[] B, int[] C, int[][] MA, int[][] ME)
        {
            int vector = VectorMult(B, C);
            int[][] MD = MatrixMult(MA, ME);
            MD = MatrixMultInt(MD, vector);
            return MD;
        }

        public static int[][] F2(int[][] MH, int[][] MK, int[][] ML)
        {
            int max = MaxMatrix(MH);
            int[][] MG = MatrixMult(MK, ML);
            MG = MatrixMultInt(MG, max);
            return MG;
        }

        public static int[] F3(int[][] MP, int[][] MR, int[] T)
        {
            int[][] matrix = MatrixMult(MP, MR);
            int max = MaxMatrix(matrix);
            return VectorMultInt(T, max);
        }

        public static void GenerateVector(int[] vector)
        {
            for (int i = 0; i < vector.Length; i++)
                vector[i] = random.Next(5);
        }

        public static void GenerateMatrix(int[][] matrix)
        {
            for (int i = 0; i < matrix.Length; i++)
            {
                matrix[i] = new int[matrix.Length];
                GenerateVector(matrix[i]);
            }
        }

        public static int[][] MatrixMult(int[][] A, int[][] B)
        {
            int[][] result = new int[A.Length][];

            for (int i = 0; i < A.Length; i++)
            {
                result[i] = new int[A.Length];
                for (int j = 0; j < A.Length; j++)
                {
                    for (int r = 0; r < A.Length; r++)
                    {
                        result[i][j] += A[i][r] * B[r][j];
                    }
                }
            }

            return result;
        }

        public static int VectorMult(int[] A, int[] B)
        {
            int result = 0;
            for (int i = 0; i < A.Length; i++)
                result += A[i] * B[i];
            return result;
        }

        public static int[] VectorMultInt(int[] A, int a)
        {
            int[] result = new int[A.Length];
            for (int i = 0; i < A.Length; i++)
                result[i] += A[i] * a;
            return result;
        }

        public static int[][] MatrixMultInt(int[][] A, int a)
        {
            int[][] result = new int[A.Length][];
            for (int i = 0; i < A.Length; i++)
                result[i] = VectorMultInt(A[i], a);
            return result;
        }

        public static int MaxVector(int[] A)
        {
            int max = A[0];

            for (int i = 1; i < A.Length; i++)
            {
                if (max < A[i])
                    max = A[i];
            }
            return max;
        }

        public static int MaxMatrix(int[][] A)
        {
            int max = A[0][0];

            for (int i = 0; i < A.Length; i++)
            {
                for (int j = 0; j < A.Length; j++)
                {
                    if (max < A[i][j])
                        max = A[i][j];
                }
            }

            return max;
        }

        public static void PrintMatrix(int[][] A)
        {
            for (int i = 0; i < A.Length; i++)
            {
                for (int j = 0; j < A.Length; j++)
                {
                    Console.Write(A[i][j] + " ");
                }
                Console.WriteLine();
            }
        }

        public static void PrintVector(int[] A)
        {
            for (int i = 0; i < A.Length; i++)
                Console.Write(A[i] + " ");
            Console.WriteLine();
        }
    }
}
