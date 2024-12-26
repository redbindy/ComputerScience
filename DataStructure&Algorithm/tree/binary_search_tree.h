#pragma once

#include <cassert>
#include <cstdlib>

namespace binary_search_tree
{
	template<typename T>
	struct bst_node_t {
		T key;

		struct bst_node_t* p_left;
		struct bst_node_t* p_right;
	};

	template<typename T>
	void destroy_recursive(bst_node_t<T>** const pp_root)
	{
		if (*pp_root == nullptr) {
			return;
		}

		destroy_recursive(&((*pp_root)->p_left));
		destroy_recursive(&((*pp_root)->p_right));

		free(*pp_root);

		*pp_root = nullptr;
	}

	template<typename T>
	bst_node_t<T>* search_recursive_or_null(bst_node_t<T>* const p_node_or_null, const T target)
	{
		int (*default_comparator)(const T, const T) = [](const T a, const T b) -> int {
			if (a == b) {
				return 0;
			}

			if (a < b) {
				return -1;
			}

			return 1;
		};

		return search_recursive_or_null(p_node_or_null, target, default_comparator);
	}

	template<typename T>
	bst_node_t<T>* search_recursive_or_null(bst_node_t<T>* const p_node_or_null, const T target, int (*compare)(const T, const T))
	{
		if (p_node_or_null == nullptr) {
			return nullptr;
		}

		if (compare(p_node_or_null->key, target) == 0) {
			return p_node_or_null;
		}

		if (compare(target, p_node_or_null->key) < 0) {
			return search_recursive_or_null(p_node_or_null->p_left, target, compare);
		}

		return search_recursive_or_null(p_node_or_null->p_right, target, compare);
	}

	template<typename T>
	bst_node_t<T>* search_or_null(bst_node_t<T>* const p_node_or_null, const T target)
	{
		bst_node_t<T>* p_node = p_node_or_null;

		while (p_node != nullptr) {

			if (p_node->key == target) {
				break;
			}

			if (target < p_node->key) {
				p_node = p_node->p_left;
			}
			else {
				p_node = p_node->p_right;
			}
		}

		return p_node;
	}

	template<typename T>
	bst_node_t<T>* insert_recursive(bst_node_t<T>* const p_node_or_null, const T value)
	{
		int (*default_comparator)(const T, const T) = [](const T a, const T b) -> int {
			if (a == b) {
				return 0;
			}

			if (a < b) {
				return -1;
			}

			return 1;
		};

		return insert_recursive(p_node_or_null, value, default_comparator);
	}

	template<typename T>
	bst_node_t<T>* insert_recursive(bst_node_t<T>* const p_node_or_null, const T value, int (*compare)(const T, const T))
	{
		if (p_node_or_null == nullptr) {
			bst_node_t<T>* const new_node = static_cast<bst_node_t<T>*>(malloc(sizeof(bst_node_t<T>)));
			assert(new_node != nullptr);

			new_node->key = value;

			new_node->p_left = nullptr;
			new_node->p_right = nullptr;

			return new_node;
		}

		if (compare(value, p_node_or_null->key) < 0) {
			p_node_or_null->p_left = insert_recursive(p_node_or_null->p_left, value, compare);
		}
		else {
			p_node_or_null->p_right = insert_recursive(p_node_or_null->p_right, value, compare);
		}

		return p_node_or_null;
	}

	template<typename T>
	bst_node_t<T>* delete_recursive(bst_node_t<T>* const p_node_or_null, const T target)
	{
		if (p_node_or_null == nullptr) {
			return nullptr;
		}

		if (p_node_or_null->key == target) {

			bst_node_t<T>* p_left = p_node_or_null->p_left;
			bst_node_t<T>* p_right = p_node_or_null->p_right;

			if (p_left != nullptr && p_right != nullptr) {

				bst_node_t<T>* p_predecessor = p_left;
				while (p_predecessor->p_right != nullptr) {
					p_predecessor = p_predecessor->p_right;
				}

				p_node_or_null->key = p_predecessor->key;

				p_node_or_null->p_left = delete_recursive(p_node_or_null->p_left, p_predecessor->key);

				return p_node_or_null;
			}

			free(p_node_or_null);

			if (p_left == nullptr) {
				return p_right;
			}

			return p_left;
		}

		if (target < p_node_or_null->key) {
			p_node_or_null->p_left = delete_recursive(p_node_or_null->p_left, target);
		}
		else {
			p_node_or_null->p_right = delete_recursive(p_node_or_null->p_right, target);
		}

		return p_node_or_null;
	}

	void print_inorder_recursive(const bst_node_t<int>* const p_node_or_null)
	{
		if (p_node_or_null == nullptr) {
			return;
		}

		print_inorder_recursive(p_node_or_null->p_left);
		printf("%d ", p_node_or_null->key);
		print_inorder_recursive(p_node_or_null->p_right);
	}
}