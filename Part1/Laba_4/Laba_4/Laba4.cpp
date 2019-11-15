// Laba4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include "data.h"
#include <iostream>
#define THREADS_NUMBER 3
using namespace std;

int n = 0;
int **MD, **MG;
int *O;

DWORD WINAPI ThreadF1(CONST LPVOID lpParam)
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
	}

	GenerateMatrix(&MA, n);
	GenerateMatrix(&ME, n);
	CreateVector(&B, n);
	CreateVector(&C, n);
	F1(n, B, C, MA, ME, &MD);
	cout << "F1 finished" << endl;
	ExitThread(0);
}

DWORD WINAPI ThreadF2(CONST LPVOID lpParam)
{
	cout << "F2 started" << endl;
	int** MH = new int*[n];
	int** MK = new int*[n];
	int** ML = new int*[n];

	for (int i = 0; i < n; i++)
	{
		MH[i] = new int[n];
		MK[i] = new int[n];
		ML[i] = new int[n];
	}

	GenerateMatrix(&MH, n);
	GenerateMatrix(&MK, n);
	GenerateMatrix(&ML, n);
	F2(n, MH, MK, ML, &MG);
	cout << "F2 finished" << endl;
	ExitThread(0);
}

DWORD WINAPI ThreadF3(CONST LPVOID lpParam)
{
	cout << "F3 started" << endl;
	int* T = new int[n];
	int** MP = new int*[n];
	int** MR = new int*[n];
	for (int i = 0; i < n; i++)
	{
		MP[i] = new int[n];
		MR[i] = new int[n];
	}

	GenerateMatrix(&MP, n);
	GenerateMatrix(&MR, n);
	CreateVector(&T, n);
	F3(n, MP, MR, T, &O);
	cout << "F3 finished" << endl;
	ExitThread(0);
}

int main()
{
	cout << "Input n: " << endl;
	cin >> n;
	MD = new int*[n];
	MG = new int*[n];
	O = new int[n];
	for (int i = 0; i < n; i++)
	{
		MD[i] = new int[n];
		MG[i] = new int[n];
	}

	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE hThreads[THREADS_NUMBER];
	hThreads[0] = CreateThread(NULL, 0, &ThreadF1, hMutex, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, &ThreadF2, hMutex, 0, NULL);
	hThreads[2] = CreateThread(NULL, 0, &ThreadF3, hMutex, 0, NULL);
	WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);
	cout << "\nResult of F1: MD = (B*C)*(MA*ME):\n";
	PrintMatrix(n, MD);
	cout<<"\nResult of F2: MG = TRANS(MH) * (MK*ML):\n";
	PrintMatrix(n, MG);
	cout << "\nResult of F3: O = MAX(MP*MR) * T:\n";
	PrintVector(n, O);
    return 0;
}





