#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void CreateVector(int** p, int n);
void GenerateMatrix(int***p, int n);
void F1(int n);
void F2(int n);
void F3(int n);
void MatrixMult(int n, int** A, int** B, int*** result);
int VectorMult(int n, int *A, int* B);
void VectorMultInt(int n, int** A, int a);
void MatrixMultInt(int n, int*** A, int a);
int MaxVector(int n, int* A);
int  MaxMatrix(int n, int** A);
void PrintMatrix(int n, int** A);
void PrintVector(int n, int* A);

void CreateVector(int** p, int n)
{
	for (int i = 0; i < n; i++)
		(*p)[i] = rand() % 5;
}

void GenerateMatrix(int***p, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*p)[i][j] = rand() % 5;
}

void F1(int n, int** result)
{
	cout << "F1 started" << endl;

	int* B = new int[n];
	int* C = new int[n];
	int** MA = new int*[n];
	int** ME = new int*[n];

	for (int i = 0; i < n; i++)
	{
		MA[i] = new int[n];
		ME[i] = new int[n];
		B[i] = 1;
		C[i] = 1;
		for (int j = 0; j < n; j++)
		{
			MA[i][j] = 1;
			ME[i][j] = 1;
		}
	}

	int vector = VectorMult(n, B, C);
	MatrixMult(n, MA, ME, &result);
	MatrixMultInt(n, &result, vector);

	cout << "F1 finished" << endl;
}

void F2(int n, int** result)
{
	cout << "F2 started" << endl;

	int **mult = new int*[n];
	int** MH = new int*[n];
	int** MK = new int*[n];
	int** ML = new int*[n];

	for (int i = 0; i < n; i++)
	{
		MH[i] = new int[n];
		MK[i] = new int[n];
		ML[i] = new int[n];
		mult[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			MH[i][j] = 1;
			MK[i][j] = 1;
			ML[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int prom = MH[i][j];
			MH[i][j] = MH[j][i];
			MH[j][i] = prom;
		}
	}

	MatrixMult(n, MK, ML, &mult);
	MatrixMult(n, MH, mult, &result);

	cout << "F2 finished" << endl;
}

void F3(int n, int* result)
{
	cout << "F3 started" << endl;
	
	int **MP = new int*[n];
	int **ME = new int*[n];
	int** MR = new int*[n];
	int** mult = new int*[n];
	int *T = new int[n];

	for (int i = 0; i < n; i++)
	{
		MP[i] = new int[n];
		MR[i] = new int[n];
		ME[i] = new int[n];
		mult[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			MP[i][j] = 1;
			MR[i][j] = 1;
			ME[i][j] = 1;
			mult[i][j] = 0;
		}
		T[i] = 1;
	}

	MatrixMult(n, MP, MR, &mult);
	int max = MaxMatrix(n, mult);
	for (int i = 0; i < n; i++)
		result[i] = T[i];
	VectorMultInt(n, &result, max);

	cout << "F3 finished" << endl;
}

void MatrixMult(int n, int** A, int** B, int*** result)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*result)[i][j] = 0;
			for (int r = 0; r < n; r++)
				(*result)[i][j] += A[i][r] * B[r][j];
		}
	}
}

int VectorMult(int n, int *A, int* B)
{
	int result = 0;
	for (int i = 0; i < n; i++)
		result += A[i] * B[i];
	return result;
}

void VectorMultInt(int n, int** A, int a)
{
	for (int i = 0; i < n; i++)
		(*A)[i] = (*A)[i] * a;
}

void MatrixMultInt(int n, int*** A, int a)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*A)[i][j] = (*A)[i][j] * a;
}

int MaxVector(int n, int* A) 
{
	int max = A[0];

	for (int i = 1; i < n; i++)
	{
		if (max < A[i])
			max = A[i];
	}
	return max;
}

int  MaxMatrix(int n, int** A)
{
	int max = A[0][0];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (max < A[i][j])
				max = A[i][j];
		}
	}

	return max;
}

void PrintMatrix(int n, int** A)
{
	for (int i = 0; i < n; i++)
		PrintVector(n, A[i]);
}

void PrintVector(int n, int* A)
{
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

void PrintResult(int n, int** result1, int** result2, int* result3)
{
	cout << "\nResult of F1: MD = (B*C)*(MA*ME):\n";
	PrintMatrix(n, result1);
	cout << "\nResult of F2: MG = TRANS(MH) * (MK*ML):\n";
	PrintMatrix(n, result2);
	cout << "\nResult of F3: O = MAX(MP*MR) * T:\n";
	PrintVector(n, result3);
}















void F1(int n, int*** result)
{
	cout << "F1 started" << endl;

	int* B = new int[n];
	int* C = new int[n];
	int** MA = new int*[n];
	int** ME = new int*[n];

	for (int i = 0; i < n; i++)
	{
		MA[i] = new int[n];
		ME[i] = new int[n];
		B[i] = 1;
		C[i] = 1;
		for (int j = 0; j < n; j++)
		{
			MA[i][j] = 1;
			ME[i][j] = 1;
		}
	}

	int vector = VectorMult(n, B, C);
	MatrixMult(n, MA, ME, result);
	MatrixMultInt(n, result, vector);

	cout << "F1 finished" << endl;
}

void F2(int n, int*** result)
{
	cout << "F2 started" << endl;
	
	int **mult = new int*[n];
	int** MH = new int*[n];
	int** MK = new int*[n];
	int** ML = new int*[n];

	for (int i = 0; i < n; i++)
	{
		MH[i] = new int[n];
		MK[i] = new int[n];
		ML[i] = new int[n];
		mult[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			MH[i][j] = 1;
			MK[i][j] = 1;
			ML[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int prom = MH[i][j];
			MH[i][j] = MH[j][i];
			MH[j][i] = prom;
		}
	}

	MatrixMult(n, MK, ML, &mult);
	MatrixMult(n, MH, mult, result);

	cout << "F2 finished" << endl;
}

void F3(int n, int** result)
{
	cout << "F3 started" << endl;

	int **MP = new int*[n];
	int **ME = new int*[n];
	int** MR = new int*[n];
	int** mult = new int*[n];
	int *T = new int[n];

	for (int i = 0; i < n; i++)
	{
		MP[i] = new int[n];
		MR[i] = new int[n];
		ME[i] = new int[n];
		mult[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			MP[i][j] = 1;
			MR[i][j] = 1;
			ME[i][j] = 1;
			mult[i][j] = 0;
		}
		T[i] = 1;
	}

	MatrixMult(n, MP, MR, &mult);
	int max = MaxMatrix(n, mult);
	for (int i = 0; i < n; i++)
		(*result)[i] = T[i];
	VectorMultInt(n, result, max);

	cout << "F3 finished" << endl;
}