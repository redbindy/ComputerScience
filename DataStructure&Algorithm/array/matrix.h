#pragma once

#include <stdio.h>

namespace matrix
{
	enum {
		ROWS = 3,
		COLS = 3,
		MAX_COUNT = 100
	};

	void transpose(const int input[ROWS][COLS], int output[ROWS][COLS]);
	void print(const int mat[ROWS][COLS]);

	namespace sparse
	{
		typedef struct element {
			int row;
			int col;
			int value;
		} element_t;

		typedef struct sparse_matrix {
			element elements[MAX_COUNT];
			int rows;
			int cols;
			int values;
		} sparse_matrix_t;

		void transpose(const sparse_matrix_t* p_input, sparse_matrix_t* p_output);
		void print(const sparse_matrix_t* p_mat);
	};
}