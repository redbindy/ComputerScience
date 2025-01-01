#pragma once

#include <cassert>
#include <cstdlib>
#include <cmath>

#include "../queue/ring_queue.h"

namespace avl_tree
{
	typedef struct node {
		int key;

		struct node* p_left;
		struct node* p_right;
	} node_t;

	void destroy_recursive(node_t** const pp_node);

	node_t* search_recursive_or_null(node_t* const p_node_or_null, const int key);
	node_t* insert_recursive(node_t* const p_node_or_null, const int key);
	node_t* delete_recursive_or_null(node_t* const p_node_or_null, const int key);
	int get_height_recursive(const node_t* const p_node_or_null);
};