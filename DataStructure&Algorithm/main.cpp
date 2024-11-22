#include <cstdio>
#include <cassert>
#include <cmath>
#include <cfloat>

#include "recursion/recursion.h"
#include "array/array.h"
#include "array/polynomial.h"
#include "array/matrix.h"
#include "stack/stack.h"
#include "stack/stack_application.h"

void test_recursion();
void test_array();
void test_stack();

int main(void)
{
	// test_recursion();
	// test_array();
	test_stack();

	return 0;
}

void test_recursion()
{
	// factorial
	{
		uint32_t n = 0;
		uint32_t expected = 1;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_tail_recursive(n) == expected);
		assert(get_factorial(n) == expected);

		n = 1;
		expected = 1;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_tail_recursive(n) == expected);
		assert(get_factorial(n) == expected);

		n = 2;
		expected = 2;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_tail_recursive(n) == expected);
		assert(get_factorial(n) == expected);

		n = 10;
		expected = 3'628'800;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial(n) == expected);
	}

	// power
	{
		double base = 2;
		uint32_t exponent = 0;
		double expected = 1;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 1;
		expected = 2;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 10;
		expected = 1024;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		base = 3;
		exponent = 0;
		expected = 1;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 1;
		expected = 3;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 5;
		expected = 243;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);
	}

	// fibonacci
	{
		uint32_t n = 0;
		uint32_t expected = 0;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);

		n = 1;
		expected = 1;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);

		n = 2;
		expected = 1;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);

		n = 16;
		expected = 987;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);
	}

	// Hanoi
	{
		solve_hanoi_recursive(6);
	}

	// binomial coefficient
	{
		uint32_t n = 1;
		uint32_t k = 0;
		uint32_t expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		k = 1;
		expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 3;
		k = 0;
		expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 3;
		k = 3;
		expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 3;
		k = 1;
		expected = 3;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 10;
		k = 5;
		expected = 252;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);
	}
}


void test_array()
{
	// ADT
	array_t<int> array = array_create<int>(10);
	{
		// assert
		// array_set(&array, 10, 10);

		// success
		array_set<int>(&array, 0, 10);
		assert(array_get<int>(&array, 0) == 10);

		array_set<int>(&array, 9, 10);
		assert(array_get<int>(&array, 9) == 10);
	}
	array_delete(&array);

	// polynomial
	{
		polynomial_t a = { 5, { 3, 6, 0, 0, 0, 10 } };
		polynomial_print(&a);

		polynomial_t b = { 4, { 7, 0, 5, 0, 1 } };
		polynomial_print(&b);

		polynomial_t c = polynomial_add(&a, &b);
		polynomial_print(&c);
	}

	// polynomial_term
	{
		const int lhs_start = 0;
		const int lhs_end = 2;
		polynomial_term_print(lhs_start, lhs_end);

		const int rhs_start = 3;
		const int rhs_end = 5;
		polynomial_term_print(rhs_start, rhs_end);

		int result_start = -1;
		int result_end = -1;
		polynomial_term_add(lhs_start, lhs_end, rhs_start, rhs_end, &result_start, &result_end);

		assert(result_start >= 0);
		assert(result_end >= 0);
		polynomial_term_print(result_start, result_end);
	}

	// matrix
	{
		int mat[ROWS][COLS] = {
			{ 2, 3, 0 },
			{ 8, 9, 1 },
			{ 7, 0, 5 }
		};
		matrix_print(mat);

		int transposed[ROWS][COLS];
		matrix_transpose(mat, transposed);

		matrix_print(transposed);
	}

	// sparse_matrix
	{
		sparse_matrix m = {
			{
				{ 0, 3, 7 },
				{ 1, 0, 9 },
				{ 1, 5, 8 },
				{ 3, 0, 6 },
				{ 3, 1, 5 },
				{ 4, 5, 1 },
				{ 5, 2, 2 },
			},
			6,
			6,
			7
		};

		sparse_matrix_print(&m);

		sparse_matrix transposed;
		sparse_matrix_transpose(&m, &transposed);

		sparse_matrix_print(&transposed);
	}
}

void test_stack()
{
	// ADT
	stack_t<int> stack = stack_create<int>(3);
	{

		assert(!stack_is_full(&stack));
		assert(stack_is_empty(&stack));

		stack_push(&stack, 10);

		assert(stack_peek(&stack) == 10);
		assert(stack_pop(&stack) == 10);

		stack_push(&stack, 10);
		stack_push(&stack, 10);
		stack_push(&stack, 10);
		stack_push(&stack, 10);

		assert(stack.capacity == 6);
	}
	stack_delete(&stack);

	// check_parentheses
	{
		const char* input = "{ A[(i + 1)] }";
		assert(is_valid_parentheses(input, strlen(input)));

		input = "if ((i == 0) && (j == 0)";
		assert(!is_valid_parentheses(input, strlen(input)));

		input = "A[(i + 1)]) = 0;";
		assert(!is_valid_parentheses(input, strlen(input)));
	}

	// calculate postfix expression
	{
		const char* input = "8 2 / 3 -";
		assert(abs(calculate_postfix_expression(input) - 1.0) < DBL_EPSILON);

		input = "8 2 / 3 - 3 2 * +";
		assert(abs(calculate_postfix_expression(input) - 7.0) < DBL_EPSILON);
	}

	// convert infix to postfix
	{
		const char* input = "2+3 * 4+ 9";
		char output[1024] = { '\0', };

		convert_infix_to_postfix(input, output);
	}

	// can exit maze
	{
		enum {
			MAZE_WIDTH = 6,
			MAZE_HEIGHT = 6
		};

		char maze[MAZE_WIDTH][MAZE_HEIGHT] = {
			{ 'w', 'w', 'w', 'w', 'w', 'w' },
			{ ' ', ' ', 'w', ' ', ' ', 'w' },
			{ 'w', ' ', ' ', ' ', 'w', 'w' },
			{ 'w', ' ', 'w', ' ', 'w', 'w' },
			{ 'w', ' ', 'w', ' ', ' ', ' ' },
			{ 'w', 'w', 'w', 'w', 'w', 'w' }
		};

		point_t entry_point = { 0, 1 };
		point_t exit_point = { 5 , 4 };

		assert(can_exit_maze(reinterpret_cast<char*>(maze), MAZE_WIDTH, MAZE_HEIGHT, entry_point, exit_point));

		memset(maze, ' ', sizeof(char) * MAZE_WIDTH * MAZE_HEIGHT);

		assert(can_exit_maze(reinterpret_cast<char*>(maze), MAZE_WIDTH, MAZE_HEIGHT, entry_point, exit_point));

		char maze_cannot_exit[MAZE_WIDTH][MAZE_HEIGHT] = {
			{ 'w', 'w', 'w', 'w', 'w', ' ' },
			{ ' ', ' ', 'w', ' ', ' ', 'w' },
			{ 'w', ' ', ' ', ' ', 'w', 'w' },
			{ 'w', ' ', 'w', ' ', 'w', 'w' },
			{ 'w', ' ', 'w', ' ', ' ', 'w' },
			{ 'w', 'w', 'w', 'w', 'w', 'w' }
		};

		exit_point.x = 5;
		exit_point.y = 0;
		assert(!can_exit_maze(reinterpret_cast<char*>(maze_cannot_exit), MAZE_WIDTH, MAZE_HEIGHT, entry_point, exit_point));
	}
}
