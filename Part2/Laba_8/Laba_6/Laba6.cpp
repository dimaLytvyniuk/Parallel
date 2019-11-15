// Laba6.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <mpi.h>
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
	int world_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		int n = 0;

		cout << "Input n:" << endl;
		cin >> n;

		int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);
		int **MP = new int*[n];
		int **MR = new int*[n];
		int *S = new int[n];
		int *T = new int[n];

		for (int i = 0; i < n; i++)
		{
			MP[i] = new int[n];
			MR[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				MP[i][j] = 1;
				MR[i][j] = 1;
			}
			S[i] = 1;
			T[i] = 1;
		}

		MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		for (int i = 0; i < k; i++)
		{
			MPI_Send(MP[i], n, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				MPI_Send(&MR[i][j], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			}
		}

		MPI_Send(&n, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		for (int i = k; i < n; i++)
		{
			MPI_Send(MP[i], n, MPI_INT, 2, 0, MPI_COMM_WORLD);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = k; j < n; j++)
			{
				MPI_Send(&MR[i][j], 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
			}
		}
		
		MPI_Send(&n, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
		MPI_Send(S, n, MPI_INT, 3, 0, MPI_COMM_WORLD);
		MPI_Send(&n, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
		MPI_Send(T, n, MPI_INT, 4, 0, MPI_COMM_WORLD);
	} 
	else if (world_rank == 1) {
		int n = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);
		
		int **MP = new int*[n];
		int **MR = new int*[n];
		int **MPMR = new int*[n];
		for (int i = 0; i < n; i++)
		{
			MP[i] = new int[n];
			MR[i] = new int[n];
			MPMR[i] = new int[n];
		}

		for (int i = 0; i < k; i++)
		{
			MPI_Recv(MP[i], n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				MPI_Recv(&MR[i][j], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			}
		}

		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				MPMR[i][j] = 0;
				for (int r = 0; r < n; r++)
				{
					MPMR[i][j] += MP[i][r] * MR[r][j];
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				MPI_Send(&MR[i][j], 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = k; j < n; j++)
			{
				MPI_Recv(&MR[i][j], 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			}
		}

		for (int i = 0; i < k; i++)
		{
			for (int j = k; j < n; j++)
			{
				MPMR[i][j] = 0;
				for (int r = 0; r < n; r++)
				{
					MPMR[i][j] += MP[i][r] * MR[r][j];
				}
			}
		}

		for (int i = 0; i < k; i++)
		{
			MPI_Send(MPMR[i], n, MPI_INT, 3, 0, MPI_COMM_WORLD);
		}
	}
	else if (world_rank == 2) {
		int n = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);

		int **MP = new int*[n];
		int **MR = new int*[n];
		int **MPMR = new int*[n];
		for (int i = 0; i < n; i++)
		{
			MP[i] = new int[n];
			MR[i] = new int[n];
			MPMR[i] = new int[n];
		}

		for (int i = k; i < n; i++)
		{
			MPI_Recv(MP[i], n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = k; j < n; j++)
			{
				MPI_Recv(&MR[i][j], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			}
		}

		for (int i = k; i < n; i++)
		{
			for (int j = k; j < n; j++)
			{
				MPMR[i][j] = 0;
				for (int r = 0; r < n; r++)
				{
					MPMR[i][j] += MP[i][r] * MR[r][j];
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				MPI_Recv(&MR[i][j], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = k; j < n; j++)
			{
				MPI_Send(&MR[i][j], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			}
		}

		for (int i = k; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				MPMR[i][j] = 0;
				for (int r = 0; r < n; r++)
				{
					MPMR[i][j] += MP[i][r] * MR[r][j];
				}
			}
		}

		for (int i = k; i < n; i++)
		{
			MPI_Send(MPMR[i], n, MPI_INT, 3, 0, MPI_COMM_WORLD);
		}
	}
	else if (world_rank == 3) {
		int n = 0;
		int *S = new int[n];
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		MPI_Recv(S, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

		int k = n % 2 == 0 ? n / 2 : (n / 2 + 1);
		int **MPMR = new int*[n];
		int *SMPMR = new int[n];
		for (int i = 0; i < n; i++)
		{
			MPMR[i] = new int[n];
		}
		for (int i = 0; i < k; i++)
		{
			MPI_Recv(MPMR[i], n, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}
		for (int i = k; i < n; i++)
		{
			MPI_Recv(MPMR[i], n, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}

		for (int i = 0; i < n; i++)
		{
			SMPMR[i] = 0;
			for (int j = 0; j < n; j++)
			{
				SMPMR[i] += MPMR[i][j] * S[j];
			}
		}

		MPI_Send(SMPMR, n, MPI_INT, 4, 0, MPI_COMM_WORLD);
	}
	else if (world_rank == 4) {
		int n = 0;

		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int *T = new int[n];
		MPI_Recv(T, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int *SMPMR = new int[n];
		MPI_Recv(SMPMR, n, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		int *O = new int[n];

		for (int i = 0; i < n; i++)
		{
			O[i] = T[i] + SMPMR[i];
		}
		cout << "O=S*(MP*MR)+T" << endl;
		for (int i = 0; i < n; i++)
			cout <<O[i]<< " ";
	}

	MPI_Finalize();
	return 0;
}

