#pragma once

#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "../stack/stack.h"
#include "../queue/ring_queue.h"

namespace binary_tree
{
	template<typename T>
	struct binary_tree_node_t {
		T data;

		binary_tree_node_t* p_left;
		binary_tree_node_t* p_right;
	};

	template<typename T>
	struct binary_tree_array_t {
		T* p_data;
		bool* p_exist;

		size_t capacity;
	};

	void print_preorder_recursive(const binary_tree_node_t<int>* const p_tree_node_or_null)
	{
		if (p_tree_node_or_null == nullptr) {
			return;
		}

		printf("%d ", p_tree_node_or_null->data);
		print_preorder_recursive(p_tree_node_or_null->p_left);
		print_preorder_recursive(p_tree_node_or_null->p_right);
	}

	void print_preorder_recursive(const binary_tree_array_t<int>* const p_tree, const size_t index)
	{
		assert(p_tree != nullptr);
		assert(p_tree->p_data != nullptr);
		assert(p_tree->p_exist != nullptr);

		if (index >= p_tree->capacity || !p_tree->p_exist[index]) {
			return;
		}

		printf("%d ", p_tree->p_data[index]);
		print_preorder_recursive(p_tree, index * 2);
		print_preorder_recursive(p_tree, index * 2 + 1);
	}

	void print_preorder(const binary_tree_node_t<int>* const p_tree_node)
	{
		assert(p_tree_node != nullptr);

		using namespace stack;

		stack_t<const binary_tree_node_t<int>*> stack = create<const binary_tree_node_t<int>*>(10);

		push(&stack, p_tree_node);

		while (!is_empty(&stack)) {
			const binary_tree_node_t<int>* const p_node = pop(&stack);

			if (p_node == nullptr) {
				continue;
			}

			printf("%d ", p_node->data);

			push<const binary_tree_node_t<int>*>(&stack, p_node->p_right);
			push<const binary_tree_node_t<int>*>(&stack, p_node->p_left);
		}
	}

	void print_inorder_recursive(const binary_tree_node_t<int>* const p_tree_node_or_null)
	{
		if (p_tree_node_or_null == nullptr) {
			return;
		}

		print_inorder_recursive(p_tree_node_or_null->p_left);
		printf("%d ", p_tree_node_or_null->data);
		print_inorder_recursive(p_tree_node_or_null->p_right);
	}

	void print_inorder(const binary_tree_node_t<int>* const p_tree_node)
	{
		assert(p_tree_node != nullptr);

		using namespace stack;

		stack_t<const binary_tree_node_t<int>*> stack = create<const binary_tree_node_t<int>*>(10);

		const binary_tree_node_t<int>* p_node = p_tree_node;
		while (true) {
			for (; p_node != nullptr; p_node = p_node->p_left) {
				push(&stack, p_node);
			}

			if (is_empty(&stack)) {
				break;
			}

			p_node = pop(&stack);
			printf("%d ", p_node->data);

			p_node = p_node->p_right;
		}
	}

	void print_postorder_recursive(const binary_tree_node_t<int>* const p_tree_node_or_null)
	{
		if (p_tree_node_or_null == nullptr) {
			return;
		}

		print_postorder_recursive(p_tree_node_or_null->p_left);
		print_postorder_recursive(p_tree_node_or_null->p_right);
		printf("%d ", p_tree_node_or_null->data);
	}

	void print_postorder(const binary_tree_node_t<int>* const p_tree_node)
	{
		assert(p_tree_node != nullptr);

		using namespace stack;

		stack_t<const binary_tree_node_t<int>*> stack = create<const binary_tree_node_t<int>*>(10);

		const binary_tree_node_t<int>* p_node = p_tree_node;
		const binary_tree_node_t<int>* p_visited_node = nullptr;

		while (true) {
			for (; p_node != nullptr; p_node = p_node->p_left) {
				push(&stack, p_node);
			}

			while (true) {

				if (is_empty(&stack)) {
					return;
				}

				p_node = pop(&stack);

				if (p_node->p_right != nullptr && p_node->p_right != p_visited_node) {
					push(&stack, p_node);
					p_node = p_node->p_right;

					break;
				}

				printf("%d ", p_node->data);
				p_visited_node = p_node;
			}
		}
	}

	void print_bfs(const binary_tree_node_t<int>* const p_tree_node)
	{
		assert(p_tree_node != nullptr);

		using namespace ring_queue;

		ring_queue_t<const binary_tree_node_t<int>*> queue = create<const binary_tree_node_t<int>*>(10);
		enqueue(&queue, p_tree_node);

		while (!is_empty(&queue)) {
			const binary_tree_node_t<int>* const p_node = dequeue(&queue);

			if (p_node == nullptr) {
				continue;
			}

			printf("%d ", p_node->data);

			enqueue<const binary_tree_node_t<int>*>(&queue, p_node->p_left);
			enqueue<const binary_tree_node_t<int>*>(&queue, p_node->p_right);
		}
	}

	template<typename T>
	int get_node_count_recursive(const binary_tree_node_t<T>* const p_tree_node_or_null)
	{
		if (p_tree_node_or_null == nullptr) {
			return 0;
		}

		const int left_count = get_node_count_recursive(p_tree_node_or_null->p_left);
		const int right_count = get_node_count_recursive(p_tree_node_or_null->p_right);

		return 1 + left_count + right_count;
	}

	template<typename T>
	int get_leaf_count_recursive(const binary_tree_node_t<T>* const p_tree_node_or_null)
	{
		if (p_tree_node_or_null == nullptr) {
			return 0;
		}

		if (p_tree_node_or_null->p_left == nullptr && p_tree_node_or_null->p_right == nullptr) {
			return 1;
		}

		const int left_leaf_count = get_leaf_count_recursive(p_tree_node_or_null->p_left);
		const int right_leaf_count = get_leaf_count_recursive(p_tree_node_or_null->p_right);

		return left_leaf_count + right_leaf_count;
	}

	template<typename T>
	int get_height_recursive(const binary_tree_node_t<T>* const p_tree_node_or_null)
	{
		if (p_tree_node_or_null == nullptr) {
			return 0;
		}

		const int left_height = get_height_recursive(p_tree_node_or_null->p_left);
		const int right_height = get_height_recursive(p_tree_node_or_null->p_right);

		int height = 1;
		if (left_height > right_height) {
			height += left_height;
		}
		else {
			height += right_height;
		}

		return height;
	}
}