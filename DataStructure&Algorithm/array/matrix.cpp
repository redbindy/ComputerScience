#include "matrix.h"

void matrix::transpose(const int input[ROWS][COLS], int output[ROWS][COLS])
{
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			output[col][row] = input[row][col];
		}
	}
}

void matrix::print(const int mat[ROWS][COLS])
{
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			printf("%d ", mat[row][col]);
		}
		printf("\n");
	}
	printf("\n");
}

void matrix::sparse::transpose(const sparse_matrix_t* p_input, sparse_matrix_t* p_output)
{
	*p_output = *p_input;
	p_output->rows = p_input->cols;
	p_output->cols = p_input->rows;

	if (p_input->values == 0) {
		return;
	}

	int output_index = 0;
	for (int col = 0; col < p_input->cols; ++col) {
		for (int i = 0; i < p_input->values; ++i) {
			if (col == p_input->elements[i].col) {
				p_output->elements[output_index].row = p_input->elements[i].col;
				p_output->elements[output_index].col = p_input->elements[i].row;
				p_output->elements[output_index].value = p_input->elements[i].value;

				++output_index;
			}
		}
	}
}

void matrix::sparse::print(const sparse_matrix_t* p_mat)
{
	printf("(row, col, value)\n");
	for (int i = 0; i < p_mat->values; ++i) {
		printf("(%d, %d, %d)\n", p_mat->elements[i].row, p_mat->elements[i].col, p_mat->elements[i].value);
	}
	printf("\n");
}
