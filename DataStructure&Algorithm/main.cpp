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
#include "queue/linear_queue.h"
#include "queue/ring_queue.h"
#include "queue/queue_application.h"
#include "queue/deque.h"

void test_recursion();
void test_array();
void test_stack();
void test_queue();

int main(void)
{
	// test_recursion();
	// test_array();
	// test_stack();
	test_queue();

	return 0;
}

void test_recursion()
{
	// recursion
	{
		using namespace recursion;
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
}


void test_array()
{
	// ADT
	{
		using namespace array;
		array_t<int> array = create<int>(10);
		{
			// assert
			// array_set(&array, 10, 10);

			// success
			set<int>(&array, 0, 10);
			assert(get<int>(&array, 0) == 10);

			set<int>(&array, 9, 10);
			assert(get<int>(&array, 9) == 10);
		}
		delete_array(&array);
	}

	// polynomial
	{
		using namespace polynomial;
		{
			polynomial_t a = { 5, { 3, 6, 0, 0, 0, 10 } };
			print(&a);

			polynomial_t b = { 4, { 7, 0, 5, 0, 1 } };
			print(&b);

			polynomial_t c = add(&a, &b);
			print(&c);
		}
	}

	// polynomial_term
	{
		using namespace polynomial::term;
		{
			const int lhs_start = 0;
			const int lhs_end = 2;
			print(lhs_start, lhs_end);

			const int rhs_start = 3;
			const int rhs_end = 5;
			print(rhs_start, rhs_end);

			int result_start = -1;
			int result_end = -1;
			add(lhs_start, lhs_end, rhs_start, rhs_end, &result_start, &result_end);

			assert(result_start >= 0);
			assert(result_end >= 0);
			print(result_start, result_end);
		}
	}

	// matrix
	{
		using namespace matrix;
		{
			int mat[ROWS][COLS] = {
				{ 2, 3, 0 },
				{ 8, 9, 1 },
				{ 7, 0, 5 }
			};
			print(mat);

			int transposed[ROWS][COLS];
			transpose(mat, transposed);

			print(transposed);
		}
	}

	// sparse_matrix
	{
		using namespace matrix::sparse;
		{
			sparse_matrix_t m = {
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

			print(&m);

			sparse_matrix_t transposed;
			transpose(&m, &transposed);

			print(&transposed);
		}
	}
}

void test_stack()
{
	// ADT
	{
		using namespace stack;
		stack_t<int> stack = create<int>(3);
		{
			assert(!is_full(&stack));
			assert(is_empty(&stack));

			push(&stack, 10);

			assert(peek(&stack) == 10);
			assert(pop(&stack) == 10);

			push(&stack, 10);
			push(&stack, 10);
			push(&stack, 10);
			push(&stack, 10);

			assert(stack.capacity == 6);
		}
		delete_stack(&stack);
	}

	// stack_application
	{
		using namespace stack_application;
		{
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
	}
}

void test_queue()
{
	// linear queue
	{
		using namespace linear_queue;
		linear_queue_t<int> linear_queue = create<int>(3);
		{
			assert(is_empty(&linear_queue));
			assert(!is_full(&linear_queue));

			enqueue(&linear_queue, 10);
			enqueue(&linear_queue, 10);
			enqueue(&linear_queue, 10);

			assert(is_full(&linear_queue));

			enqueue(&linear_queue, 10);

			assert(dequeue(&linear_queue) == 10);
			assert(dequeue(&linear_queue) == 10);
			assert(dequeue(&linear_queue) == 10);
			assert(dequeue(&linear_queue) == 10);

			assert(is_empty(&linear_queue));
		}
		delete_linear_queue(&linear_queue);
	}

	// ring queue
	{
		using namespace ring_queue;
		ring_queue_t<int> ring_queue = create<int>(4);
		{
			assert(is_empty(&ring_queue));
			assert(!is_full(&ring_queue));

			enqueue(&ring_queue, 10);
			assert(!is_empty(&ring_queue));
			assert(!is_full(&ring_queue));

			enqueue(&ring_queue, 10);
			enqueue(&ring_queue, 10);
			enqueue(&ring_queue, 10);

			assert(!is_empty(&ring_queue));
			assert(is_full(&ring_queue));

			assert(peek(&ring_queue) == 10);

			assert(dequeue(&ring_queue) == 10);

			enqueue(&ring_queue, 10);
			enqueue(&ring_queue, 10);

			assert(dequeue(&ring_queue) == 10);
			assert(dequeue(&ring_queue) == 10);
			assert(dequeue(&ring_queue) == 10);
			assert(dequeue(&ring_queue) == 10);
			assert(dequeue(&ring_queue) == 10);

			assert(is_empty(&ring_queue));
		}
		delete_ring_queue(&ring_queue);
	}

	// queue_application
	{
		using namespace queue_application;
		// simulate producer consumer
		{
			simulate_producer_consumer();
		}
	}

	// deque
	{
		using namespace deque;
		deque_t<int> deque = create<int>(3);
		{
			assert(is_empty(&deque));
			assert(!is_full(&deque));

			add_front(&deque, 1);

			assert(!is_empty(&deque));
			assert(!is_full(&deque));

			add_back(&deque, 2);
			add_back(&deque, 3);

			assert(!is_empty(&deque));
			assert(is_full(&deque));

			assert(remove_front(&deque) == 1);
			assert(remove_front(&deque) == 2);
			assert(remove_front(&deque) == 3);
			assert(is_empty(&deque));

			add_front(&deque, 1);
			add_front(&deque, 2);
			add_back(&deque, 3);
			add_back(&deque, 4);

			assert(!is_empty(&deque));
			assert(!is_full(&deque));

			assert(remove_back(&deque) == 4);
			assert(remove_back(&deque) == 3);
			assert(remove_back(&deque) == 1);
			assert(remove_back(&deque) == 2);
		}
		delete_deque(&deque);
	}
}
