#include "avl_tree.h"

namespace avl_tree
{
	void destroy_recursive(node_t** const pp_node)
	{
		assert(pp_node != nullptr);

		if (*pp_node == nullptr) {
			return;
		}

		node_t** const pp_left = &((*pp_node)->p_left);
		destroy_recursive(pp_left);

		node_t** const pp_right = &((*pp_node)->p_right);
		destroy_recursive(pp_right);

		free(*pp_node);

		*pp_node = nullptr;
	}

	node_t* search_recursive_or_null(node_t* const p_node_or_null, const int key)
	{
		if (p_node_or_null == nullptr) {
			return nullptr;
		}

		if (p_node_or_null->key == key) {
			return p_node_or_null;
		}

		if (key < p_node_or_null->key) {
			return search_recursive_or_null(p_node_or_null->p_left, key);
		}

		return search_recursive_or_null(p_node_or_null->p_right, key);
	}

	static node_t* rotate_left(node_t* const p_node)
	{
		assert(p_node != nullptr);

		node_t* const p_right = p_node->p_right;
		node_t* const p_right_left = p_right->p_left;

		p_node->p_right = p_right_left;
		p_right->p_left = p_node;

		return p_right;
	}

	static node_t* rotate_right(node_t* const p_node)
	{
		assert(p_node != nullptr);

		node_t* const p_left = p_node->p_left;
		node_t* const p_left_right = p_left->p_right;

		p_node->p_left = p_left_right;
		p_left->p_right = p_node;

		return p_left;
	}

	static node_t* rebalance_tree(node_t* const p_node, const int key)
	{
		assert(p_node != nullptr);

		node_t* const p_left = p_node->p_left;
		node_t* const p_right = p_node->p_right;

		const int left_height = get_height_recursive(p_left);
		const int right_height = get_height_recursive(p_right);

		const int balance_factor = left_height - right_height;

		if (abs(balance_factor) <= 1) {
			return p_node;
		}

		if (balance_factor > 0) {

			if (key > p_node->p_left->key) {
				p_node->p_left = rotate_left(p_node->p_left);
			}

			return rotate_right(p_node);
		}

		if (key < p_node->p_right->key) {
			p_node->p_right = rotate_right(p_node->p_right);
		}

		return rotate_left(p_node);
	}

	node_t* insert_recursive(node_t* const p_node_or_null, const int key)
	{
		if (p_node_or_null == nullptr) {

			node_t* const p_node = static_cast<node_t*>(malloc(sizeof(node_t)));
			assert(p_node != nullptr);

			p_node->key = key;

			p_node->p_left = nullptr;
			p_node->p_right = nullptr;

			return p_node;
		}

		node_t* const p_left = p_node_or_null->p_left;
		node_t* const p_right = p_node_or_null->p_right;

		if (key < p_node_or_null->key) {
			p_node_or_null->p_left = insert_recursive(p_left, key);
		}
		else {
			p_node_or_null->p_right = insert_recursive(p_right, key);
		}

		return rebalance_tree(p_node_or_null, key);
	}

	node_t* delete_recursive_or_null(node_t* const p_node_or_null, const int key)
	{
		if (p_node_or_null == nullptr) {
			return nullptr;
		}

		node_t* const p_left = p_node_or_null->p_left;
		node_t* const p_right = p_node_or_null->p_right;

		if (p_node_or_null->key == key) {

			if (p_left != nullptr && p_right != nullptr) {

				node_t* p_predecessor = p_left;
				while (p_predecessor->p_right != nullptr) {
					p_predecessor = p_predecessor->p_right;
				}

				const int predecessor_key = p_predecessor->key;

				p_node_or_null->p_left = delete_recursive_or_null(p_left, predecessor_key);

				p_node_or_null->key = predecessor_key;

				return p_node_or_null;
			}

			free(p_node_or_null);

			if (p_right == nullptr) {
				return p_left;
			}

			return p_right;
		}

		if (key < p_node_or_null->key) {
			p_node_or_null->p_left = delete_recursive_or_null(p_left, key);
		}
		else {
			p_node_or_null->p_right = delete_recursive_or_null(p_right, key);
		}

		return rebalance_tree(p_node_or_null, key);
	}

	int get_height_recursive(const node_t* const p_node_or_null)
	{
		if (p_node_or_null == nullptr) {
			return 0;
		}  

		const int left_height = get_height_recursive(p_node_or_null->p_left);
		const int right_height = get_height_recursive(p_node_or_null->p_right);

		const int max = left_height > right_height ? left_height : right_height;

		return 1 + max;
	}
}
