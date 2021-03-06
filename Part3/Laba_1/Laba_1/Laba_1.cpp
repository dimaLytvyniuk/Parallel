﻿// Laba_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <mpi.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fstream>
#include <cmath> 

using namespace std;

const char* input_file_name = "../../in.txt";
const char* output_file_name = "out.txt";
const double EPSILON = 1E-16;

const int X_TAG = 0;
const int VALUE_TAG = 1;

int world_rank;
int numprocs;
double x;

double getX(const char* fileName) {
	double param;

	ifstream fin(fileName);
	fin >> param;

	return param;
}

double calculateElement(double x, int n) {
	return (pow(-1, n + 1) * pow(x, n)) / n;
}

double writeResult(const char* fileName, double result) {
	FILE* output_file = fopen(fileName, "w");
	if (!output_file) {
		fprintf(stderr, "Can’t open output file !\n\n");
		MPI_Abort(MPI_COMM_WORLD, 2);
		return 2;
	}

	fprintf(output_file, " % .8lf\n", result);
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		x = getX(input_file_name);

		for (int i = 1; i < numprocs; i++) {
			MPI_Send(&x, 1, MPI_DOUBLE, i, X_TAG, MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(&x, 1, MPI_DOUBLE, 0, X_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	double sum = .0;
	int term_number = world_rank + 1;
	bool isEnd = false;

	for (int step = 0; step < 1000000; step++) {
		double currentValue = calculateElement(x, term_number);
		sum += currentValue;

		if (abs(currentValue) < EPSILON) {
			// cout << step << endl;
			break;
		}

		term_number += numprocs;
	}

	if (world_rank == 0) {
		for (int i = 1; i < numprocs; i++) {
			double taskResult;
			MPI_Recv(&taskResult, 1, MPI_DOUBLE, i, VALUE_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += taskResult;
		}
	}
	else {
		MPI_Send(&sum, 1, MPI_DOUBLE, 0, VALUE_TAG, MPI_COMM_WORLD);
	}

	if (world_rank == 0) {
		cout << "Sum: " << sum << endl;
		writeResult(output_file_name, sum);
	}

	MPI_Finalize();
	return 0;
}
