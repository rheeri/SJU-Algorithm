#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)
#define N 8

typedef struct Matrix {
	double **matrix;
	int size;
}Matrix;

void initMatrix(Matrix* A, int n);
void delMatrix(Matrix* A);
void inputMatrix(Matrix* A);
void printMatrix(Matrix A);
double determinant(Matrix A);
Matrix transpose(Matrix A);
Matrix minorMatrix(Matrix A, int col, int row);
Matrix cofactorMatrix(Matrix A);
Matrix adjoint(Matrix A);
Matrix inverseMatrix(Matrix A);

int main() {
	Matrix A, inverse;
	double det;

	initMatrix(&A, N);
	inputMatrix(&A);

	initMatrix(&inverse, N);
	inverse = inverseMatrix(A);
	printMatrix(inverse);

	delMatrix(&A);
	delMatrix(&inverse);
}
void initMatrix(Matrix* A, int n) {
	A->matrix = (double**)malloc(sizeof(double*)*n);
	for (int i = 0; i < n; i++) A->matrix[i] = (double*)malloc(sizeof(double)*n);
	A->size = n;
}
void delMatrix(Matrix* A) {
	for (int i = 0; i < A->size; i++) {
		free(A->matrix[i]);
	}
	free(A->matrix);
}
void inputMatrix(Matrix* A) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double x;
			scanf("%lf", &x);
			A->matrix[i][j] = x;
		}
	}
}
void printMatrix(Matrix A) {
	for (int i = 0; i < A.size; i++) {
		for (int j = 0; j < A.size; j++) {
			printf("%.3lf ", A.matrix[i][j]);
		}
		printf("\n");
	}
}
double determinant(Matrix A) {
	int sign = 1;
	double det = 0;

	if (A.size == 2) {
		det = A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];
		return det;
	}

	for (int i = 0; i < A.size; i++) {
		Matrix minor;
		initMatrix(&minor, A.size);

		minor = minorMatrix(A, 0, i);
		det = det + sign * A.matrix[i][0] * determinant(minor);
		sign *= -1;
	}
	return det;
}
Matrix transpose(Matrix A) {
	Matrix result;
	initMatrix(&result, A.size);

	for (int i = 0; i < A.size; i++) {
		for (int j = 0; j < A.size; j++) {
			result.matrix[i][j] = A.matrix[j][i];
		}
	}
}
Matrix minorMatrix(Matrix A, int col, int row) {
	Matrix result;
	int rowIndex = 0, colIndex = 0, i, j;

	initMatrix(&result, A.size - 1);
	for (int i = 0; i < A.size; i++) {
		if (i == row) {
			continue;
		}
		colIndex = 0; 
		for (int j = 0; j < A.size; j++) {
			if (j == col) {
				continue; 
			}
			result.matrix[rowIndex][colIndex++] = A.matrix[i][j];
		}
		rowIndex++;
	}


	return result;
}
Matrix cofactorMatrix(Matrix A) {
	Matrix result;
	initMatrix(&result, A.size);

	for (int i = 0; i < A.size; i++) {
		for (int j = 0; j < A.size; j++) {
			result.matrix[i][j] = determinant(minorMatrix(A, i, j));
		}
	}
	return result;
}
Matrix adjoint(Matrix A) {
	Matrix result, cofactor, transposed;
	int sign = 1;

	initMatrix(&result, A.size);
	initMatirx(&cofactor, A.size);
	initMatrix(&transposed, A.size);

	cofactor = cofactorMatrix(A);
	transposed = transpose(cofactor);
	for (int i = 0; i < A.size; i++) {
		for (int j = 0; j < A.size; j++) {
			result.matrix[i][j] = sign * transposed.matrix[i][j];
		}
	}
	delMatrix(&cofactor);
	delMatrix(&transposed);
	return result;
}
Matrix inverseMatrix(Matrix A) {
	Matrix result, tmp;
	double det = determinant(A);

	initMatirx(&result, A.size);
	initMatrix(&tmp, A.size);

	if (A.size == 2) {
		tmp.matrix[0][0] = A.matrix[1][1];
		tmp.matrix[1][1] = A.matrix[0][0];
		tmp.matrix[0][1] = -A.matrix[0][1];
		tmp.matrix[1][0] = -A.matrix[1][0];

		for (int i = 0; i < A.size; i++) {
			for (int j = 0; j < A.size; j++) {
				result.matrix[i][j] = (double)((double)1 / det) * tmp.matrix[i][j];
			}
		}
		delMatrix(&tmp);
		return result;
	}

	tmp = adjoint(A);
	for (int i = 0; i < A.size; i++) {
		for (int j = 0; j < A.size; j++) {
			result.matrix[i][j] = (double)((double)1 / det) * tmp.matrix[i][j];
		}
	}
	delMatrix(&tmp);
	return result;
}