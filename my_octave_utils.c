// Copyright 2021 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

// creating a structure for a 3d array

typedef struct {
	int **elements;
	int rows, cols;
} matrix;

// dynamically allocating a 2d array

void alloc_mat(matrix *a, int n, int m)
{
	a->elements = (int **)malloc(m * sizeof(int *));

	if (!a->elements)
		exit(404);

	for (int i = 0; i < m; i++)
		a->elements[i] = (int *)malloc(n * sizeof(int));
}

// dynamically allocating an array

int *alloc_arr(int nr)
{
	int *arr = (int *)malloc((nr + 1) * sizeof(int));
	if (!arr)
		exit(404);

	return arr;
}

// function to free the memory of a matrix

void dealloc_mem(matrix *a)
{
	for (int i = 0; i < a->rows; i++)
		free(a->elements[i]);
	free(a->elements);
}

// checking if the given index is correct

int check_index(int i, int size)
{
	if (i >= size || i < 0) {
		printf("No matrix with the given index\n");
		return 0;
	}
	return 1;
}

// printing a matrix

void print_matrix(matrix A)
{
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++)
			printf("%d ", A.elements[i][j]);
		printf("\n");
	}
}

// function to resize a given matrix

void resize_mat(int n_line, int n_col, matrix *A, int *l_arr, int *c_arr)
{
	// creating a copy

	matrix B = *A;

	// allocating memory to my initial matrix
	// changing its size with the new number of rows and columns

	alloc_mat(A, n_col, n_line);

	// each element from the row array + column array will be assigned
	// to an element from the matrix

	for (int i = 0; i < n_line; i++) {
		for (int j = 0; j < n_col; j++) {
			int new_line = l_arr[i];
			int new_col = c_arr[j];
			A->elements[i][j] = B.elements[new_line][new_col];
		}
	}

	A->rows = n_line;
	A->cols = n_col;

	// freeing the copy matrix after using it

	dealloc_mem(&B);
}

// function to multiply two matrices

void multiply_mat(matrix A, matrix B, matrix *C, int r1, int r2, int c2)
{
	C->rows = r1;
	C->cols = c2;

	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			C->elements[i][j] = 0;
			for (int k = 0; k < r2; k++) {
				C->elements[i][j] += A.elements[i][k] * B.elements[k][j];

				// avoiding integer overflow

				C->elements[i][j] = C->elements[i][j] % 10007;
				if (C->elements[i][j] < 0)
					C->elements[i][j] += 10007;
			}
		}
	}
}

// creating the transpose of a matrix

void transpose_mat(matrix *tr_A, matrix A, int row, int col)
{
	alloc_mat(tr_A, col, row);
	tr_A->rows = row;
	tr_A->cols = col;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			tr_A->elements[i][j] = A.elements[j][i];
	}
}

// calculating the sum of a given matrix

int mat_sum(matrix A)
{
	int sum = 0;
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			sum += A.elements[i][j];

			// avoiding integer overflow

			sum = sum % 10007;
			if (sum < 0)
				sum += 10007;
		}
	}

	return sum;
}

// function to swap 2 given matrixes

void swap_mat(matrix *A, int i1, int i2)
{
	matrix tmp;

	tmp = A[i1];
	A[i1] = A[i2];
	A[i2] = tmp;
}

// sorting a 3d array in ascending order

void sort_mat(matrix *A, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (mat_sum(A[i]) > mat_sum(A[j]))
				swap_mat(A, i, j);
		}
	}
}

// function for the free command

void free_mat_mem(matrix *A, int size, int index)
{
	for (int i = index; i < size - 1; i++) {
		A[i].elements = A[i + 1].elements;
		A[i].rows = A[i + 1].rows;
		A[i].cols = A[i + 1].cols;
	}
}

// printing a warning message in case of a wrong command in the input

void wrong_command_warning(char command)
{
	if (isalpha(command) && !strchr("LDPCMOTFQ", command))
		printf("Unrecognized command\n");
}

// in case the size of our 3d array has reached its limit, we'll reallocate mem

void realloc_matrix_mem(int size, int *d, matrix **A)
{
	if (size == *d) {
		*A = realloc(*A, (*d * 2) * sizeof(matrix));
		*d *= 2;
	}
}

// reading a new matrix

void read_new_mat(int m, int n, matrix new_mat)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &new_mat.elements[i][j]);
}

// assigning new values to each member of the structure

void assign_to_mat(matrix *A, matrix B, int row, int col)
{
	A->elements = B.elements;
	A->rows = row;
	A->cols = col;
}

void read_arr(int *arr, int n)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
}

// allocating memory for the 3d array

void alloc_3d_arr(matrix **A, int dim)
{
	*A = (matrix *)malloc(dim * sizeof(matrix));
	if (!*A)
		exit(404);
}

// function for the 'M' command

void multiplication_command(matrix *A, int *size)
{
	int i1, i2;
	scanf("%d%d", &i1, &i2);
	if (i1 < 0 || i2 < 0 || i1 >= *size || i2 >= *size) {
		printf("No matrix with the given index\n");
	} else if (A[i1].cols != A[i2].rows) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		matrix C;
		int r1 = A[i1].rows, r2 = A[i2].rows;
		int c2 = A[i2].cols;
		alloc_mat(&C, c2, r1);
		multiply_mat(A[i1], A[i2], &C, r1, r2, c2);
		assign_to_mat(&A[*size], C, r1, c2);
		*size = *size + 1;
	}
}
