#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

void CreateVector(int** p, int n);
void GenerateMatrix(int***p, int n);
void F1(int n, int* B, int* C, int** MA, int** ME, int*** result);
void F2(int n, int** MH, int** MK, int** ML, int*** result);
void F3(int n, int** MP, int** MR, int* T, int** result);
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

void F1(int n, int* B, int* C, int** MA, int** ME, int*** result)
{
	int vector = VectorMult(n, B, C);
	MatrixMult(n, MA, ME, result);
	MatrixMultInt(n, result, vector);
}

void F2(int n, int** MH, int** MK, int** ML, int*** result)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int prom = MH[i][j];
			MH[i][j] = MH[j][i];
			MH[j][i] = prom;
		}
	}
	int **mult = new int*[n];
	for (int i = 0; i < n; i++)
		mult[i] = new int[n];
	MatrixMult(n, MK, ML, &mult);
	MatrixMult(n, MH, mult, result);
}

void F3(int n, int** MP, int** MR, int* T, int** result)
{
	int **mult = new int*[n];
	for (int i = 0; i < n; i++)
		mult[i] = new int[n];
	MatrixMult(n, MP, MR, &mult);
	int max = MaxMatrix(n, mult);
	for (int i = 0; i < n; i++)
		(*result)[i] = T[i];
	VectorMultInt(n, result, max);
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
		(*A)[i] += (*A)[i] * a;
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
