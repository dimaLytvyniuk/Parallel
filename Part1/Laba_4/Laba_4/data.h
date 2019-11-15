#pragma once

void CreateVector(int** p, int n);
void GenerateMatrix(int***p, int n);
void F1(int n, int* B, int* C, int** MA, int** ME, int*** result);
void F2(int n, int** MH, int** MK, int** ML, int*** result);
void F3(int n, int** MP, int** MR, int* T, int** result);
void MatrixMult(int n, int** A, int** B, int*** result);
int VectorMult(int n, int *A, int* B);
void VectorMultInt(int n, int** A, int a);
void MatrixMultInt(int n, int*** A, int a);
int MaxVector(int n, int* A);
int  MaxMatrix(int n, int** A);
void PrintMatrix(int n, int** A);
void PrintVector(int n, int* A);