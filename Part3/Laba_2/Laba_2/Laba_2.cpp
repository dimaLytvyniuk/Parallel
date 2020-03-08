// Laba_1.cpp : Ётот файл содержит функцию "main". «десь начинаетс€ и заканчиваетс€ выполнение программы.
//
#include <mpi.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fstream>
#include <cmath> 
#include <sstream>

using namespace std;

const char* input_file_name = "../../in.txt";
const char* output_file_name = "out.txt";
const double EPSILON = 1E-8;

const int INPUT_TAG = 0;
const int RESULT_TAG = 1;

int world_rank;
int numprocs;

double* getInput(const char* fileName) {
	double input[3];

	ifstream fin(fileName);
	fin >> input[0] >> input[1] >> input[2];

	return input;
}

double writeResult(const char* fileName, double result) {
	FILE* output_file = fopen(fileName, "w");
	if (!output_file) {
		fprintf(stderr, "CanТt open output file !\n\n");
		MPI_Abort(MPI_COMM_WORLD, 2);
		return 2;
	}

	fprintf(output_file, " % .8lf\n", result);
}

double function(double x)
{
	return log2(pow(x, 3));
}

bool check_Runge(double I2, double I, double epsilon)
{
	return (abs(I2 - I) / 3.) < epsilon;
}

double integrate_right_rectangle(double start, double finish, double epsilon)
{
	int num_iterations = 1;
	double last_res = 0.;
	double res = -1.;
	double h = 0.;
	
	while (!check_Runge(res, last_res, epsilon))
	{
		num_iterations *= 2;
		last_res = res;
		res = 0.;
		h = (finish - start) / num_iterations;
		for (int i = 1; i <= num_iterations; i++)
		{
			res += abs(function(start + i * h)) * h;
		}
	}

	return res;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	double input[3];
	MPI_Request* send_input_reqs = new MPI_Request[numprocs - 1];
	if (world_rank == 0) {
		double* file_input = getInput(input_file_name);
		for (int i = 0; i < 3; i++) {
			input[i] = file_input[i];
		}

		for (int i = 1; i < numprocs; i++) {
			MPI_Isend(input, 3, MPI_DOUBLE, i, INPUT_TAG, MPI_COMM_WORLD, &send_input_reqs[i - 1]);
		}

		MPI_Waitall(numprocs - 1, send_input_reqs, MPI_STATUSES_IGNORE);
	}
	else {
		MPI_Request recv_req;
		MPI_Irecv(&input, 3, MPI_DOUBLE, 0, INPUT_TAG, MPI_COMM_WORLD, &recv_req);
		MPI_Wait(&recv_req, MPI_STATUS_IGNORE);
	}

	double step = (input[1] - input[0]) / numprocs;
	double start = input[0] + world_rank * step;
	double finish = start + step;

	double epsilon = input[2];
	double res = integrate_right_rectangle(start, finish, epsilon);

	if (world_rank != 0) {
		MPI_Request send_req;
		MPI_Isend(&res, 1, MPI_DOUBLE, 0, RESULT_TAG, MPI_COMM_WORLD, &send_req);
		MPI_Wait(&send_req, MPI_STATUS_IGNORE);
	}
	else {
		MPI_Request* recv_input_reqs = new MPI_Request[numprocs - 1];
		double* results = new double[numprocs - 1];
		
		for (int i = 1; i < numprocs; i++) {
			MPI_Irecv(&results[i - 1], 1, MPI_DOUBLE, i, RESULT_TAG, MPI_COMM_WORLD, &recv_input_reqs[i - 1]);
		}
		
		MPI_Waitall(numprocs - 1, recv_input_reqs, MPI_STATUS_IGNORE);
		
		for (int i = 0; i < numprocs - 1; i++) {
			res += results[i];
		}

		//cout << "Result: " << res << endl;
		writeResult(output_file_name, res);

		delete[] recv_input_reqs;
		delete[] results;
	}

	delete[] send_input_reqs;

	MPI_Finalize();
	return 0;
}
