// Laba6.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <mpi.h>
#include <iostream>
#include "data.h"
#include <ctime>

using namespace std;

int world_rank;
int numprocs;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		int n = 0;
		cout << "Input n:" << endl;
		cin >> n;
		MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&n, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		MPI_Send(&n, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
		MPI_Send(&n, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
	} 
	else if (world_rank == 1) {
		int n = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int **result = new int*[n];
		for (int i = 0; i < n; i++)
			result[i] = new int[n];
		F1(n, &result);
		for (int i = 0; i < n; i++)
			MPI_Send(result[i], n, MPI_INT, 4, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 2) {
		int n = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int **result = new int*[n];
		for (int i = 0; i < n; i++)
			result[i] = new int[n];
		F2(n, &result);
		for (int i = 0; i < n; i++)
			MPI_Send(result[i], n, MPI_INT, 4, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 3) {
		int n = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int *result = new int[n];
		F3(n, &result);
		MPI_Send(result, n, MPI_INT, 4, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 4) {
		int n = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int** result1 = new int*[n];
		int** result2 = new int*[n];
		int* result3 = new int[n];

		for (int i = 0; i < n; i++)
		{
			result1[i] = new int[n];
			result2[i] = new int[n];
		}

		for (int i = 0; i < n; i++)
			MPI_Recv(result1[i], n, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		for (int i = 0; i < n; i++)
			MPI_Recv(result2[i], n, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		
		MPI_Recv(result3, n, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		PrintResult(n, result1, result2, result3);
	}

	MPI_Finalize();
	return 0;
}

