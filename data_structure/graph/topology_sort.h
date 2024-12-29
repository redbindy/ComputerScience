#pragma once

#include <cassert>
#include <cstring>
#include <cstdio>

#include "../list/singly_linked_list.h"
#include "../stack/stack.h"

namespace topology_sort
{
	using namespace singly_linked_list;
	using namespace stack;

	typedef struct grpah {
		node_t<int>** pp_adj_list;
		
		int capacity;
	} graph_t;

	graph_t create_graph(const int capacity);
	void destroy_graph(graph_t* const p_this);

	void insert_edge(graph_t* const p_this, const int start, const int end);

	void print_topology_sort(const graph_t* const p_this);
}