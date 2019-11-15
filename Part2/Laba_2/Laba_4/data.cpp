#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#define THREADS_NUMBER 3
using namespace std;

CRITICAL_SECTION critsect;
HANDLE ghMKEvent;
HANDLE ghMLEvent;

void CreateVector(int** p, int n);
void GenerateMatrix(int***p, int n);
void F1(int n, int*** MG, int** MK, int** ML);
int  MaxMatrix(int n, int** A);
void PrintMatrix(int n, int** A);
void PrintVector(int n, int* A);
DWORD WINAPI ThreadMAX(CONST LPVOID lpParam);
DWORD WINAPI ThreadMK(CONST LPVOID lpParam);
DWORD WINAPI ThreadML(CONST LPVOID lpParam);

int ***MGC, **MKC, **MLC, **MKML, max, nc;

void CreateVector(int** p, int n)
{
	for (int i = 0; i < n; i++)
		(*p)[i] = rand() % 5;
}

void GenerateMatrix(int***p, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			//(*p)[i][j] = rand() % 5;
			(*p)[i][j] = 1;
}

void F1(int n, int*** MG, int** MK, int** ML)
{
	MGC = MG;
	MKC = MK;
	MLC = ML;
	nc = n;

	MKML = new int*[n];
	for (int i = 0; i < n; i++)
	{
		MKML[i] = new int[n];
	}


	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE hThreads[THREADS_NUMBER];
	InitializeCriticalSection(&critsect);

	ghMLEvent = CreateEvent(NULL,TRUE,FALSE,TEXT("MLEvent"));
	ghMKEvent = CreateEvent(NULL,TRUE,FALSE,TEXT("MKEvent"));


	hThreads[0] = CreateThread(NULL, 0, &ThreadMAX, hMutex, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, &ThreadMK, hMutex, 0, NULL);
	hThreads[2] = CreateThread(NULL, 0, &ThreadML, hMutex, 0, NULL);
	WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			(*MGC)[i][j] = max * MKML[i][j];
		}
	}
}

DWORD WINAPI ThreadMAX(CONST LPVOID lpParam)
{
	max = MaxMatrix(nc, (*MGC));
	ExitThread(0);
}

DWORD WINAPI ThreadMK(CONST LPVOID lpParam)
{
	int k = nc % 2 == 0 ? nc / 2 : (nc / 2 + 1);
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			MKML[i][j] = 0;
			for (int r = 0; r < nc; r++)
			{
				MKML[i][j] += MKC[i][r] * MLC[r][j];
			}
		}
	}
	SetEvent(ghMKEvent);
	WaitForSingleObject(ghMLEvent, INFINITE);

	for (int i = 0; i < k; i++)
	{
		for (int j = k; j < nc; j++)
		{
			MKML[i][j] = 0;
			for (int r = 0; r < nc; r++)
			{
				MKML[i][j] += MKC[i][r] * MLC[r][j];
			}
		}
	}
	ExitThread(0);
}

DWORD WINAPI ThreadML(CONST LPVOID lpParam)
{
	int k = nc % 2 == 0 ? nc / 2 : (nc / 2 + 1);
	for (int i = k; i < nc; i++)
	{
		for (int j = k; j < nc; j++)
		{
			MKML[i][j] = 0;
			for (int r = 0; r < nc; r++)
			{
				MKML[i][j] += MKC[i][r] * MLC[r][j];
			}
		}
	}

	SetEvent(ghMLEvent);
	WaitForSingleObject(ghMKEvent, INFINITE);

	for (int i = k; i < nc; i++)
	{
		for (int j = 0; j < k; j++)
		{
			MKML[i][j] = 0;
			for (int r = 0; r < nc; r++)
			{
				MKML[i][j] += MKC[i][r] * MLC[r][j];
			}
		}
	}

	ExitThread(0);
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
