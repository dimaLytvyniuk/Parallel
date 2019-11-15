#pragma once

void CalcFunc(int** MG, int** ML, int*** MF, int k, int n);
void MultMatrix(int** MG, int** ML, int*** MGML, int k, int n);
void MultMatrixNumber(int** MG, int*** KMG, int k, int n);
void MinusMatrixes(int** MG, int** ML, int*** MGML, int n);
void PrintMatrix(int n, int** A);
void PrintVector(int n, int* A);
void GenerateMatrix(int***p, int n);