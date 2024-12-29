#pragma once

#include <cassert>

namespace binary_tree_application
{
	typedef struct node {
		int data;

		struct node* p_left;
		struct node* p_right;
	} node_t;

	int evaluate_expression_recursive(const node_t* const p_tree_node);
	int calculate_folder_size_recursive(const node_t* const p_tree_node);
}