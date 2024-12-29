#pragma once

#include <cassert>
#include <cstdio>

namespace threaded_binary_tree
{
	template<typename T>
	struct threaded_tree_node_t {
		T data;

		struct threaded_tree_node_t* p_left;
		struct threaded_tree_node_t* p_right;

		bool is_thread;
	};

	void print_inorder(const threaded_tree_node_t<char>* const p_tree)
	{
		assert(p_tree != nullptr);

		const threaded_tree_node_t<char>* p_node = p_tree;
		while (p_node->p_left != nullptr) {
			p_node = p_node->p_left;
		}

		do {
			printf("%c ", p_node->data);

			const threaded_tree_node_t<char>* p_successor = p_node->p_right;
			if (p_successor != nullptr && !p_node->is_thread) {
				while (p_successor->p_left != nullptr) {
					p_successor = p_successor->p_left;
				}
			}

			p_node = p_successor;

		} while (p_node != nullptr);
	}
}