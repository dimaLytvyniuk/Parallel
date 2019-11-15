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
	cout << "Input n:" << endl;
	cin >> n;

	#pragma omp parallel sections
	{
		#pragma omp section
		F1(n);

		#pragma omp section
		F2(n);

		#pragma omp section
		F3(n);
	}

    return 0;
}

