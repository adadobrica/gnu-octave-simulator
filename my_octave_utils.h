// Copyright 2021 Dobrica Nicoleta Adriana 311CA
typedef struct {
	int **elements;
	int rows, cols;
} matrix;

void alloc_mat(matrix *a, int n, int m);
int *alloc_arr(int nr);
void dealloc_mem(matrix *a);
int check_index(int i, int size);
void print_matrix(matrix A);
void resize_mat(int n_line, int n_col, matrix *A, int *l_arr, int *c_arr);
void multiply_mat(matrix A, matrix B, matrix *C, int r1, int r2, int c2);
void transpose_mat(matrix *tr_A, matrix A, int row, int col);
int mat_sum(matrix A);
void swap_mat(matrix *A, int i1, int i2);
void sort_mat(matrix *A, int size);
void free_mat_mem(matrix *A, int size, int index);
void wrong_command_warning(char command);
void realloc_matrix_mem(int size, int *d, matrix **A);
void read_new_mat(int m, int n, matrix new_mat);
void assign_to_mat(matrix *A, matrix B, int row, int col);
void read_arr(int *arr, int n);
void alloc_3d_arr(matrix **A, int dim);
void multiplication_command(matrix *A, int *size);
