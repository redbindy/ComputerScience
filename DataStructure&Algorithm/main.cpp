#include <cassert>
#include <cmath>
#include <cfloat>
#include <cstdint>
#include <cstring>

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
#include "list/array_list.h"
#include "list/singly_linked_list.h"
#include "list/linked_list_application.h"
#include "list/ring_liked_list.h"
#include "list/doubly_linked_list.h"
#include "list/linked_stack.h"
#include "list/linked_queue.h"
#include "tree/binary_tree.h"
#include "tree/binary_tree_application.h"
#include "tree/threaded_binary_tree.h"
#include "tree/binary_search_tree.h"

void test_recursion();
void test_array();
void test_stack();
void test_queue();
void test_list();
void test_tree();

int main(void)
{
	// test_recursion();
	// test_array();
	// test_stack();
	// test_queue();
	// test_list();
	test_tree();

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
			double coeff = 2;
			uint32_t exp = 0;
			double expected = 1;
			assert(abs(get_power(coeff, exp) - expected) <= DBL_EPSILON);
			assert(abs(get_power_recursive(coeff, exp) - expected) <= DBL_EPSILON);

			exp = 1;
			expected = 2;
			assert(abs(get_power(coeff, exp) - expected) <= DBL_EPSILON);
			assert(abs(get_power_recursive(coeff, exp) - expected) <= DBL_EPSILON);

			exp = 10;
			expected = 1024;
			assert(abs(get_power(coeff, exp) - expected) <= DBL_EPSILON);
			assert(abs(get_power_recursive(coeff, exp) - expected) <= DBL_EPSILON);

			coeff = 3;
			exp = 0;
			expected = 1;
			assert(abs(get_power(coeff, exp) - expected) <= DBL_EPSILON);
			assert(abs(get_power_recursive(coeff, exp) - expected) <= DBL_EPSILON);

			exp = 1;
			expected = 3;
			assert(abs(get_power(coeff, exp) - expected) <= DBL_EPSILON);
			assert(abs(get_power_recursive(coeff, exp) - expected) <= DBL_EPSILON);

			exp = 5;
			expected = 243;
			assert(abs(get_power(coeff, exp) - expected) <= DBL_EPSILON);
			assert(abs(get_power_recursive(coeff, exp) - expected) <= DBL_EPSILON);
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

void test_list()
{
	// array list
	{
		using namespace array_list;
		array_list_t<int> array_list = create<int>(3);
		{
			assert(is_empty(&array_list));
			assert(!is_full(&array_list));

			add_item(&array_list, 10);

			assert(!is_empty(&array_list));
			assert(!is_full(&array_list));
			assert(get_item(&array_list, 0));

			add_item(&array_list, 20);
			insert_at(&array_list, 0, 1);

			assert(array_list.count == 3);
			assert(!is_empty(&array_list));
			assert(is_full(&array_list));

			assert(get_item(&array_list, 0) == 1);
			assert(get_item(&array_list, 1) == 10);
			assert(get_item(&array_list, 2) == 20);

			clear(&array_list);

			assert(is_empty(&array_list));
			assert(!is_full(&array_list));

			insert_at(&array_list, 0, 10);
			add_item(&array_list, 20);
			insert_at(&array_list, 1, 30);
			add_item(&array_list, 40);

			assert(!is_empty(&array_list));
			assert(!is_full(&array_list));

			assert(get_item(&array_list, 0) == 10);
			assert(get_item(&array_list, 1) == 30);
			assert(get_item(&array_list, 2) == 20);
			assert(get_item(&array_list, 3) == 40);
		}
		delete_array_list(&array_list);
	}

	// singly linked list
	{
		using namespace singly_linked_list;
		node_t<int>* p_head = create_singly_node_malloc(0);
		{
			print_list(p_head);

			add_front(&p_head, 1);
			add_front(&p_head, 2);
			add_back(&p_head, 3);
			add_back(&p_head, 4);

			print_list(p_head);

			remove_item(&p_head, 0);

			print_list(p_head);

			remove_item(&p_head, 3);

			print_list(p_head);
		}
		destroy(&p_head);

		p_head = create_singly_node_malloc(0);
		{
			print_list(p_head);

			p_head = add_last_recursive(p_head, 1);
			p_head = add_last_recursive(p_head, 2);
			p_head = add_last_recursive(p_head, 3);
			p_head = add_last_recursive(p_head, 4);

			print_list(p_head);

			p_head = remove_item_recursive(p_head, 3);

			print_list(p_head);
		}
		destroy_recursive(&p_head);

		p_head = create_singly_node_malloc(0);
		{
			add_front(&p_head, 1);
			add_front(&p_head, 2);
			add_front(&p_head, 3);
			add_front(&p_head, 4);
			add_front(&p_head, 5);

			print_list(p_head);

			reverse_list(&p_head);

			print_list(p_head);

			p_head = reverse_list_recursive<int>(nullptr, p_head);

			print_list(p_head);
		}
		destroy(&p_head);

		node_t<int>* p_node0 = create_singly_node_malloc(0);
		node_t<int>* p_node1 = create_singly_node_malloc(10);
		{
			add_front(&p_node0, 1);
			add_front(&p_node0, 2);
			add_front(&p_node0, 3);
			add_front(&p_node0, 4);
			add_front(&p_node0, 5);

			print_list(p_node0);

			add_front(&p_node1, 20);
			add_front(&p_node1, 30);
			add_front(&p_node1, 40);
			add_front(&p_node1, 50);
			add_front(&p_node1, 60);

			print_list(p_node1);

			interleave_recursive(p_node0, p_node1);
			p_node1 = nullptr;

			print_list(p_node0);
		}
		destroy(&p_node0);

		p_node0 = create_singly_node_malloc(0);
		p_node1 = create_singly_node_malloc(10);
		{
			add_front(&p_node0, 1);
			add_front(&p_node0, 2);
			add_front(&p_node0, 3);
			add_front(&p_node0, 4);
			add_front(&p_node0, 5);

			print_list(p_node0);

			add_front(&p_node1, 20);
			add_front(&p_node1, 30);
			add_front(&p_node1, 40);
			add_front(&p_node1, 50);
			add_front(&p_node1, 60);

			print_list(p_node1);

			interleave(p_node0, p_node1);
			p_node1 = nullptr;

			print_list(p_node0);
		}
		destroy(&p_node0);
	}

	// linked list application
	{
		using namespace linked_list_application;
		term_node_t* p_lhs = make_term_malloc(5, 3);
		{
			print_polynomial(p_lhs);

			term_node_t* p_rhs = make_term_malloc(4, 3);

			print_polynomial(p_rhs);

			add_polynomial(&p_lhs, p_rhs);

			print_polynomial(p_lhs);
		}
		destroy_polynomial(&p_lhs);

		p_lhs = make_term_malloc(1, 1);
		{
			term_node_t* p_rhs = make_term_malloc(1, -1);

			add_polynomial(&p_lhs, p_rhs);
		}
		destroy_polynomial(&p_lhs);

		p_lhs = make_term_malloc(5, 3);
		{
			add_polynomial(&p_lhs, make_term_malloc(-5, 3));
			add_polynomial(&p_lhs, make_term_malloc(4, 2));
			add_polynomial(&p_lhs, make_term_malloc(1, 1));
			add_polynomial(&p_lhs, make_term_malloc(0, 10));

			print_polynomial(p_lhs);

			term_node_t* p_rhs = make_term_malloc(5, 3);
			add_polynomial(&p_rhs, make_term_malloc(4, -2));
			add_polynomial(&p_rhs, make_term_malloc(-3, -2));
			add_polynomial(&p_rhs, make_term_malloc(0, -5));

			print_polynomial(p_rhs);

			add_polynomial(&p_lhs, p_rhs);

			print_polynomial(p_lhs);
		}
		destroy_polynomial(&p_lhs);
	}

	// ring linked list
	{
		using namespace ring_linked_list;
		node_t<int>* p_node = create_ring_node_malloc(1);
		{
			add_front(&p_node, 2);
			add_front(&p_node, 3);

			print_list(p_node);
		}
		destroy(&p_node);

		p_node = create_ring_node_malloc(1);
		{
			add_back(&p_node, 2);
			add_back(&p_node, 3);

			print_list(p_node);
		}
		destroy(&p_node);

		// ring linked list application - multi-player game
		node_t<const char*>* p_game_turn = create_ring_node_malloc("Player1");
		{
			add_back(&p_game_turn, "Player2");
			add_back(&p_game_turn, "Player3");

			p_game_turn = p_game_turn->p_next;
			for (int i = 0; i < 10; ++i) {
				printf("Turn %d: %s\n", i + 1, p_game_turn->data);
				p_game_turn = p_game_turn->p_next;
			}
		}
		destroy(&p_game_turn);
	}

	// doubly linked list
	{
		using namespace doubly_linked_list;
		node_t<int>* p_node = create_doubly_node_malloc(1);
		{
			add_prev(p_node, 2);
			add_prev(p_node, 3);
			add_next(p_node, 10);
			add_next(p_node, 20);
			add_next(p_node, 30);

			print_list(p_node);
		}
		destroy(&p_node);

		// doubly linked list application - mp3 player
		node_t<const char*>* p_name_node = create_doubly_node_malloc("s0");
		{
			add_next(p_name_node, "s1");
			add_next(p_name_node, "s2");
			add_next(p_name_node, "s3");
			add_next(p_name_node, "s4");
			add_next(p_name_node, "s5");

			printf("a: prev d: next x: escape\n");
			printf("----------start----------\n");
			printf("Playing: %s\n", p_name_node->data);
			while (true) {
				const char input = getchar();

				switch (input) {
				case 'a':
					p_name_node = p_name_node->p_prev;
					printf("Playing: %s\n", p_name_node->data);
					break;

				case 'd':
					p_name_node = p_name_node->p_next;
					printf("Playing: %s\n", p_name_node->data);
					break;

				case 'x':
					goto END;

				default:
					break;
				}
			}
		END:
			printf("-----------end-----------\n");
		}
		destroy(&p_name_node);
	}

	// linked stack
	{
		using namespace linked_stack;
		linked_stack_t<int> stack = create(1);
		{
			printf("%d ", peek(&stack));
			push(&stack, 2);
			printf("%d ", peek(&stack));
			push(&stack, 3);
			printf("%d ", peek(&stack));

			printf("%d ", pop(&stack));
			printf("%d ", pop(&stack));
			printf("%d ", pop(&stack));
			printf("\n");
		}
		linked_stack::destroy(&stack);
	}

	// linked queue
	{
		using namespace linked_queue;
		linked_queue_t<int> queue = create(1);
		{
			printf("%d ", peek(&queue));
			enqueue(&queue, 2);
			printf("%d ", peek(&queue));
			enqueue(&queue, 3);
			printf("%d ", peek(&queue));

			printf("%d ", dequeue(&queue));
			printf("%d ", dequeue(&queue));
			printf("%d ", dequeue(&queue));
			printf("\n");
		}
		destroy(&queue);
	}
}

void test_tree()
{
	// binary tree traversal
	{
		using namespace binary_tree;
		binary_tree_array_t<int> tree;
		tree.capacity = 15;

		tree.p_data = static_cast<int*>(malloc(sizeof(int) * tree.capacity));
		tree.p_exist = static_cast<bool*>(malloc(sizeof(bool) * tree.capacity));
		assert(tree.p_exist != nullptr);

		memset(tree.p_exist, false, sizeof(bool) * tree.capacity);
		{
			tree.p_data[1] = 17;
			tree.p_data[2] = 15;
			tree.p_data[3] = 93;
			tree.p_data[4] = 5;
			tree.p_data[6] = 35;
			tree.p_data[7] = 95;
			tree.p_data[12] = 22;

			tree.p_exist[1] = true;
			tree.p_exist[2] = true;
			tree.p_exist[3] = true;
			tree.p_exist[4] = true;
			tree.p_exist[6] = true;
			tree.p_exist[7] = true;
			tree.p_exist[12] = true;

			print_preorder_recursive(&tree, 1);

			printf("\n");
		}
		free(tree.p_exist);
		free(tree.p_data);

		binary_tree_node_t<int>* p_root = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
		assert(p_root != nullptr);

		p_root->data = 17;
		{
			binary_tree_node_t<int>* p_node0 = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
			assert(p_node0 != nullptr);
			p_node0->data = 15;

			binary_tree_node_t<int>* p_node1 = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
			assert(p_node1 != nullptr);
			p_node1->data = 93;

			binary_tree_node_t<int>* p_node2 = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
			assert(p_node2 != nullptr);
			p_node2->data = 5;

			binary_tree_node_t<int>* p_node3 = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
			assert(p_node3 != nullptr);
			p_node3->data = 35;

			binary_tree_node_t<int>* p_node4 = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
			assert(p_node4 != nullptr);
			p_node4->data = 95;

			binary_tree_node_t<int>* p_node5 = static_cast<binary_tree_node_t<int>*>(malloc(sizeof(binary_tree_node_t<int>)));
			assert(p_node5 != nullptr);
			p_node5->data = 22;
			{
				p_root->p_left = p_node0;
				p_root->p_right = p_node1;

				p_node0->p_left = p_node2;
				p_node0->p_right = nullptr;

				p_node1->p_left = p_node3;
				p_node1->p_right = p_node4;

				p_node2->p_left = nullptr;
				p_node2->p_right = nullptr;

				p_node3->p_left = p_node5;
				p_node3->p_right = nullptr;

				p_node4->p_left = nullptr;
				p_node4->p_right = nullptr;

				p_node5->p_left = nullptr;
				p_node5->p_right = nullptr;

				print_preorder_recursive(p_root);
				printf("\n");

				print_inorder_recursive(p_root);
				printf("\n");

				print_postorder_recursive(p_root);
				printf("\n");

				print_preorder(p_root);
				printf("\n");

				print_inorder(p_root);
				printf("\n");

				print_postorder(p_root);
				printf("\n");

				print_bfs(p_root);
				printf("\n");

				printf("%d\n", get_node_count_recursive(p_root));
				printf("%d\n", get_leaf_count_recursive(p_root));
				printf("%d\n", get_height_recursive(p_root));
			}
			free(p_node5);
			free(p_node4);
			free(p_node3);
			free(p_node2);
			free(p_node1);
			free(p_node0);
		}
		free(p_root);
	}

	// binary tree application
	{
		using namespace binary_tree_application;
		using namespace binary_tree;
		{
			node_t n1 = { 1, nullptr, nullptr };
			node_t n2 = { 4, nullptr, nullptr };
			node_t n3 = { '*', &n1, &n2 };
			node_t n4 = { 16, nullptr, nullptr };
			node_t n5 = { 25, nullptr, nullptr };
			node_t n6 = { '+', &n4, &n5 };
			node_t n7 = { '+', &n3, &n6 };

			const node_t* const p_root = &n7;

			printf("%d\n", evaluate_expression_recursive(p_root));
		}

		{
			node_t n4 = { 500, nullptr, nullptr };
			node_t n5 = { 200, nullptr, nullptr };
			node_t n3 = { 100, &n4, &n5 };
			node_t n2 = { 50, nullptr, nullptr };
			node_t n1 = { 0, &n2, &n3 };

			printf("%d\n", calculate_folder_size_recursive(&n1));
		}
	}

	// threaded binary tree
	{
		using namespace threaded_binary_tree;
		{
			threaded_tree_node_t<char> n1 = { 'A', nullptr, nullptr, true };
			threaded_tree_node_t<char> n2 = { 'B', nullptr, nullptr, true };
			threaded_tree_node_t<char> n3 = { 'C', &n1, &n2, true };
			threaded_tree_node_t<char> n4 = { 'D', nullptr, nullptr, true };
			threaded_tree_node_t<char> n5 = { 'E', nullptr, nullptr, false };
			threaded_tree_node_t<char> n6 = { 'F', &n4, &n5, false };
			threaded_tree_node_t<char> n7 = { 'G', &n3, &n6, false };

			n1.p_right = &n3;
			n2.p_right = &n7;
			n4.p_right = &n6;

			print_inorder(&n7);
			printf("\n");
		}
	}

	// binary search tree
	{
		using namespace binary_search_tree;
		bst_node_t<int>* p_root = insert_recursive<int>(nullptr, 35);
		{
			p_root = insert_recursive(p_root, 18);
			p_root = insert_recursive(p_root, 68);
			p_root = insert_recursive(p_root, 7);
			p_root = insert_recursive(p_root, 26);
			p_root = insert_recursive(p_root, 3);
			p_root = insert_recursive(p_root, 12);
			p_root = insert_recursive(p_root, 22);
			p_root = insert_recursive(p_root, 30);
			p_root = insert_recursive(p_root, 99);

			assert(search_recursive_or_null(p_root, 7)->key == 7);
			assert(search_recursive_or_null(p_root, 100) == nullptr);

			print_inorder_recursive(p_root);
			printf("\n");

			delete_recursive(p_root, 30);
			print_inorder_recursive(p_root);
			printf("\n");

			delete_recursive(p_root, 68);
			print_inorder_recursive(p_root);
			printf("\n");

			delete_recursive(p_root, 18);
			print_inorder_recursive(p_root);
			printf("\n");
		}
		destroy_recursive(&p_root);

		bst_node_t<const char*>* p_dictionary = insert_recursive<const char*>(nullptr, "abc", strcmp);
		{
			p_dictionary = insert_recursive(p_dictionary, "bc", strcmp);
			p_dictionary = insert_recursive(p_dictionary, "c", strcmp);
			p_dictionary = insert_recursive(p_dictionary, "aab", strcmp);
			p_dictionary = insert_recursive(p_dictionary, "aaa", strcmp);
		}
		destroy_recursive(&p_dictionary);
	}
}
