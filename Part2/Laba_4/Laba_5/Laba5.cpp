// Laba5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <omp.h>
#include <ctime>
#include "data.h"
#include <iostream>

using namespace std;

int main()
{
	int n = 0;
	int k = 0;
	cout << "Input n:" << endl;
	cin >> n;
	cout << "Input k:" << endl;
	cin >> k;

	int** MG = new int*[n];
	int** ML = new int*[n];
	int** MF = new int*[n];
	for (int i = 0; i < n; i++)
	{
		MG[i] = new int[n];
		ML[i] = new int[n];
		MF[i] = new int[n];
	}
	GenerateMatrix(&MG, n);
	GenerateMatrix(&ML, n);

	CalcFunc(MG, ML, &MF, k, n);
	PrintMatrix(n, MF);
	
    return 0;
}

