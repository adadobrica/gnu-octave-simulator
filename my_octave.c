// Copyright 2021 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "my_octave_utils.h"
#define MAX 100

int main(void)
{
	int m, n, d = MAX, size = 0, index;
	matrix *A;
	char command;
	alloc_3d_arr(&A, d);
	scanf("%c", &command);

	while (command != 'Q') {
		if (command == 'L') {
			scanf("%d%d", &m, &n);
			matrix new_mat;
			alloc_mat(&new_mat, n, m);	// allocating mem to the matrix
			read_new_mat(m, n, new_mat);	// reading the matrix
			assign_to_mat(&A[size], new_mat, m, n); // adding to the 3d array
			size++;

			// doubling the size of the matrix if it reached its limit

			realloc_matrix_mem(size, &d, &A);
		}

		if (command == 'D') {
			scanf("%d", &index);
			if (check_index(index, size) == 1)
				printf("%d %d\n", A[index].rows, A[index].cols);
		}

		if (command == 'P') {
			scanf("%d", &index);
			if (check_index(index, size) == 1)
				print_matrix(A[index]);
		}

		if (command == 'C') {
			int num_lines, num_cols, *lines_arr, *col_arr;
			scanf("%d", &index);
			if (check_index(index, size) == 1) {
				scanf("%d", &num_lines);
				lines_arr = alloc_arr(num_lines);
				read_arr(lines_arr, num_lines);
				scanf("%d", &num_cols);
				col_arr = alloc_arr(num_cols);
				read_arr(col_arr, num_cols);
				resize_mat(num_lines, num_cols, &A[index], lines_arr, col_arr);
				free(lines_arr);
				free(col_arr);
			}
		}

		if (command == 'M')
			multiplication_command(A, &size);

		if (command == 'O')
			sort_mat(A, size);

		if (command == 'T') {
			scanf("%d", &index);
			if (check_index(index, size) == 1) {
				matrix tr_A;
				transpose_mat(&tr_A, A[index], A[index].cols, A[index].rows);
				dealloc_mem(&A[index]);
				assign_to_mat(&A[index], tr_A, A[index].cols, A[index].rows);
			}
		}

		if (command == 'F') {
			scanf("%d", &index);
			if (check_index(index, size) == 1) {
				dealloc_mem(&A[index]);
				free_mat_mem(A, size, index);
				size--;	// decrementing the total size of our matrices
			}
		}
		scanf("%c", &command);
		wrong_command_warning(command);
	}
	for (int i = 0; i < size; i++)
		dealloc_mem(&A[i]);
	free(A);
	return 0;
}
