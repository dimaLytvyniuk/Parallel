// Laba4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include "data.h"
#include <iostream>
#define THREADS_NUMBER 3
using namespace std;

int main()
{
	int n = 0;
	cout << "Input n: " << endl;
	cin >> n;

	int** MG = new int*[n];
	int** MK = new int*[n];
	int** ML = new int*[n];
	for (int i = 0; i < n; i++)
	{
		MG[i] = new int[n];
		MK[i] = new int[n];
		ML[i] = new int[n];
	}
	GenerateMatrix(&MG, n);
	GenerateMatrix(&MK, n);
	GenerateMatrix(&ML, n);

	F1(n, &MG, MK, ML);
	cout << "\nResult of F1: MG = MAX(MG)*(MK*ML):\n";
	PrintMatrix(n, MG);
    return 0;
}





