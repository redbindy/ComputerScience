#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

namespace doubly_linked_list
{
	template<typename T>
	struct node_t {
		T data;

		node_t* p_prev;
		node_t* p_next;
	};

	template<typename T>
	node_t<T>* create_doubly_node_malloc(const T value)
	{
		node_t<T>* const p_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));
		assert(p_node != nullptr);

		p_node->data = value;

		p_node->p_prev = p_node;
		p_node->p_next = p_node;

		return p_node;
	}

	template<typename T>
	void destroy(node_t<T>** const pp_node)
	{
		assert(pp_node != nullptr);

		node_t<T>* p_node = *pp_node;
		while (true) {
			node_t<T>* p_next = p_node->p_next;

			free(p_node);

			p_node = p_next;

			if (p_node == *pp_node)
			{
				break;
			}
		}

		*pp_node = nullptr;
	}

	template<typename T>
	void add_prev(node_t<T>* const p_node, const T value)
	{
		assert(p_node != nullptr);

		node_t<T>* const p_new_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));

		node_t<T>* const p_prev = p_node->p_prev;
		node_t<T>* const p_next = p_node->p_next;

		p_new_node->data = value;

		p_new_node->p_prev = p_prev;
		p_new_node->p_next = p_node;

		p_prev->p_next = p_new_node;
		p_node->p_prev = p_new_node;
	}

	template<typename T>
	void add_next(node_t<T>* const p_node, const T value)
	{
		assert(p_node != nullptr);

		node_t<T>* const p_new_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));

		node_t<T>* const p_prev = p_node->p_prev;
		node_t<T>* const p_next = p_node->p_next;

		p_new_node->data = value;

		p_new_node->p_prev = p_node;
		p_new_node->p_next = p_next;

		p_node->p_next = p_new_node;
		p_next->p_prev = p_new_node;
	}

	template<typename T>
	void remove_value(node_t<T>* const p_node, const T value)
	{
		assert(p_node != nullptr);

		node_t<T>* p = p_node;
		while (p->data != value) {
			p = p_node->p_next;

			if (p == p_node) {
				return;
			}
		}

		node_t<T>* const p_prev = p->p_prev;
		node_t<T>* const p_next = p->p_next;

		p_prev->p_next = p_next;
		p_next->p_prev = p_prev;

		free(p_node);
	}

	void print_list(const node_t<int>* const p_node)
	{
		assert(p_node != nullptr);

		const node_t<int>* p = p_node;
		while (true) {
			printf("%d ", p->data);

			p = p->p_next;
			if (p == p_node) {
				break;
			}
		}
		printf("\n");
	}
}