#include "binary_tree_application.h"

int binary_tree_application::evaluate_expression_recursive(const node_t* const p_tree_node)
{
	if (p_tree_node == nullptr) {
		return 0;
	}

	if (p_tree_node->p_left == nullptr && p_tree_node->p_right == nullptr) {
		return p_tree_node->data;
	}

	const int lhs = evaluate_expression_recursive(p_tree_node->p_left);
	const int rhs = evaluate_expression_recursive(p_tree_node->p_right);

	switch (p_tree_node->data) {
	case '+':
		return lhs + rhs;

	case '-':
		return lhs - rhs;

	case '*':
		return lhs * rhs;

	case '/':
		assert(rhs != 0);
		return lhs / rhs;

	default:
		assert(false);
		break;
	}

	return 0;
}

int binary_tree_application::calculate_folder_size_recursive(const node_t* const p_tree_node)
{
	if (p_tree_node == nullptr) {
		return 0;
	}

	const int left_size = calculate_folder_size_recursive(p_tree_node->p_left);
	const int right_size = calculate_folder_size_recursive(p_tree_node->p_right);

	return p_tree_node->data + left_size + right_size;
}
