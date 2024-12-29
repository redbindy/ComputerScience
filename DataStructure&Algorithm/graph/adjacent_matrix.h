#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "../stack/stack.h"
#include "../queue/ring_queue.h"

namespace adjacent_matrix
{
	typedef struct graph {
		int* p_matrix;

		int capacity;
		int size;
	} graph_t;

	static inline int convert_to_index(const int row, const int col, const int size)
	{
		return row * size + col;
	}

	graph_t create_graph(const int capacity)
	{
		assert(capacity > 0);

		const int matrix_byte_size = sizeof(int) * capacity * capacity;

		graph_t ret;
		ret.p_matrix = static_cast<int*>(malloc(matrix_byte_size));
		assert(ret.p_matrix != nullptr);

		memset(ret.p_matrix, -1, matrix_byte_size);

		ret.capacity = capacity;
		ret.size = 0;

		return ret;
	}

	void destroy_graph(graph_t* const p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_matrix);

		p_this->p_matrix = nullptr;

		p_this->capacity = 0;
		p_this->size = 0;
	}

	bool is_empty(const graph_t* const p_this)
	{
		assert(p_this != nullptr);

		return p_this->size == 0;
	}

	void insert_vertex(graph_t* const p_this, const int v)
	{
		assert(p_this != nullptr);
		assert(v >= 0);
		assert(v < p_this->capacity);

		++p_this->size;

		p_this->p_matrix[convert_to_index(v, v, p_this->capacity)] = 0;
	}

	void insert_edge(graph_t* const p_this, const int start, const int end)
	{
		assert(p_this != nullptr);
		assert(start >= 0);
		assert(end >= 0);
		assert(start < p_this->size);
		assert(end < p_this->size);

		if (p_this->p_matrix[convert_to_index(start, start, p_this->capacity)] == -1) {
			insert_vertex(p_this, start);
		}

		if (p_this->p_matrix[convert_to_index(end, end, p_this->capacity)] == -1) {
			insert_vertex(p_this, end);
		}

		p_this->p_matrix[convert_to_index(start, end, p_this->capacity)] = 1;
		p_this->p_matrix[convert_to_index(end, start, p_this->capacity)] = 1;
	}

	void delete_vertex(graph_t* const p_this, const int v)
	{
		assert(p_this != nullptr);
		assert(v >= 0);
		assert(v < p_this->size);

		for (int i = 0; i < p_this->capacity; ++i) {
			p_this->p_matrix[convert_to_index(v, i, p_this->capacity)] = -1;
			p_this->p_matrix[convert_to_index(i, v, p_this->capacity)] = -1;
		}
	}

	void delete_edge(graph_t* const p_this, const int start, const int end)
	{
		assert(p_this != nullptr);
		assert(start >= 0);
		assert(end >= 0);
		assert(start < p_this->size);
		assert(end < p_this->size);

		p_this->p_matrix[convert_to_index(start, end, p_this->capacity)] = 0;
		p_this->p_matrix[convert_to_index(end, start, p_this->capacity)] = 0;
	}

	void print_adjacent(const graph_t* const p_this, const int v)
	{
		assert(p_this != nullptr);
		assert(v >= 0);
		assert(v < p_this->size);

		printf("adjacent: ");
		for (int i = 0; i < p_this->capacity; ++i) {
			if (p_this->p_matrix[convert_to_index(v, i, p_this->capacity)] <= 0) {
				continue;
			}

			printf("%d ", i);
		}
		printf("\n");
	}

	void print_adjacent_matrix(const graph_t* const p_this)
	{
		assert(p_this != nullptr);

		printf("----------\n");
		for (int row = 0; row < p_this->capacity; ++row) {
			for (int col = 0; col < p_this->capacity; ++col) {
				printf("%d ", p_this->p_matrix[convert_to_index(row, col, p_this->capacity)]);
			}
			printf("\n");
		}
		printf("----------\n");
	}

	void print_dfs_recursive(const graph_t* const p_this, const int row, bool is_discovered[])
	{
		assert(p_this != nullptr);

		is_discovered[row] = true;

		printf("%d -> ", row);

		for (int col = 0; col < p_this->capacity; ++col) {
			if (p_this->p_matrix[convert_to_index(row, col, p_this->capacity)] < 1 || is_discovered[col]) {
				continue;
			}

			print_dfs_recursive(p_this, col, is_discovered);
		}
	}

	void print_dfs(const graph_t* const p_this, bool is_discovered[])
	{
		assert(p_this != nullptr);

		using namespace stack;

		stack_t<int> stack = create<int>(p_this->size);
		{
			int start = 0;

			push(&stack, start);
			is_discovered[start] = true;

			while (!is_empty(&stack)) {

				start = pop(&stack);

				printf("%d -> ", start);

				for (int i = 0; i < p_this->capacity; ++i) {
					if (p_this->p_matrix[convert_to_index(start, i, p_this->capacity)] < 1 || is_discovered[i]) {
						continue;
					}

					is_discovered[i] = true;
					push(&stack, i);
				}
			}
		}
		delete_stack(&stack);
	}

	void print_bfs(const graph_t* const p_this, bool is_discovered[])
	{
		assert(p_this != nullptr);

		using namespace ring_queue;

		ring_queue_t<int> queue = create<int>(p_this->size);
		{
			int start = 0;

			enqueue(&queue, start);
			is_discovered[start] = true;

			while (!is_empty(&queue)) {

				start = dequeue(&queue);

				printf("%d -> ", start);

				for (int i = 0; i < p_this->capacity; ++i) {
					if (p_this->p_matrix[convert_to_index(start, i, p_this->capacity)] != 1 || is_discovered[i]) {
						continue;
					}

					enqueue(&queue, i);
					is_discovered[i] = true;
				}
			}
		}
		delete_ring_queue(&queue);
	}
}