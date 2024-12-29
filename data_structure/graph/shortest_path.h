#pragma once

#include <cassert>
#include <cstring>

#include "../list/singly_linked_list.h"
#include "../priority_queue/heap.h"

namespace shortest_path
{
	using namespace singly_linked_list;
	using namespace heap;

	typedef struct element {
		int id;
		int weight;
	} element_t;

	typedef struct list_graph {
		 node_t<element_t>** pp_adj_list;

		int capacity;
	} list_graph_t;

	typedef struct matrix_graph {
		int* p_weight_matrix;

		int capacity;
	} matrix_graph_t;

	enum {
		INF = 1 << 25
	};

	list_graph_t create_list_graph(const int capacity);
	void destroy_graph(list_graph_t* const p_this);

	matrix_graph_t create_matrix_graph(const int capacity);
	void destroy_graph(matrix_graph_t* const p_this);

	void insert_edge(list_graph_t* const p_this, const int start, const int end, const int weight);
	void insert_edge(matrix_graph_t* const p_this, const int start, const int end, const int weight);

	void print_dijkstra(const list_graph_t* const p_this, const int start);
	void print_dijkstra(const matrix_graph_t* const p_this, const int start);

	void print_floyd(const matrix_graph_t* const p_this);
}