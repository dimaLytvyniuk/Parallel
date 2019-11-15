#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

void CalcFunc(int** MG, int** ML, int*** MF, int k, int n);
void MultMatrix(int** MG, int** ML, int*** MGML, int k, int n);
void MultMatrixNumber(int** MG, int*** KMG, int k, int n);
void MinusMatrixes(int** MG, int** ML, int*** MGML, int n);
void PrintMatrix(int n, int** A);
void PrintVector(int n, int* A);
void GenerateMatrix(int***p, int n);

void CalcFunc(int** MG, int** ML, int*** MF, int k, int n)
{
	int** KMG = new int*[n];
	int** KMGML = new int*[n];
	for (int i = 0; i < n; i++)
	{
		KMG[i] = new int[n];
		KMGML[i] = new int[n];
	}

#pragma omp parallel sections
	{

#pragma omp section
		MultMatrix(MG, ML, &KMGML, k, n);

#pragma omp section
		MultMatrixNumber(MG, &KMG, k, n);
	}

	MinusMatrixes(KMG, KMGML, MF, n);
}

void MultMatrixNumber(int** MG, int*** KMG, int k, int n)
{
	int i, j;

#pragma omp parallel for
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*KMG)[i][j] = MG[i][j] * k;
}

void MultMatrix(int** MG, int** ML, int*** MGML, int k, int n)
{
	int i, j, r;

#pragma omp parallel for 
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*MGML)[i][j] = 0;
			for (r = 0; r < n; r++)
			{
				(*MGML)[i][j] += MG[i][r] * ML[r][j];
			}
			(*MGML)[i][j] *= k;
		}
	}
}

void MinusMatrixes(int** MG, int** ML, int*** MGML, int n)
{
	int i, j;
#pragma omp parallel for shared(MG, ML, MGML) private(i, j)
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			(*MGML)[i][j] = MG[i][j] - ML[i][j];
		}
	}
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

void GenerateMatrix(int***p, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*p)[i][j] = 1;
}