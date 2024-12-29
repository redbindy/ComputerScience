#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

namespace ring_linked_list
{
	template<typename T>
	struct node_t {
		T data;

		node_t* p_next;
	};

	template<typename T>
	node_t<T>* create_ring_node_malloc(const T value)
	{
		node_t<T>* const p_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));
		assert(p_node != nullptr);

		p_node->data = value;
		p_node->p_next = p_node;

		return p_node;
	}

	template<typename T>
	void destroy(node_t<T>** const pp_head)
	{
		assert(pp_head != nullptr);

		node_t<T>* p_node = *pp_head;
		while (true) {
			node_t<T>* p_next = p_node->p_next;

			free(p_node);

			p_node = p_next;

			if (p_node == *pp_head) {
				break;
			}
		}

		*pp_head = nullptr;
	}

	template<typename T>
	void add_front(node_t<T>** const pp_head, const T value)
	{
		assert(pp_head != nullptr);

		node_t<T>* const p_new_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));
		assert(p_new_node != nullptr);

		node_t<T>* p_head = *pp_head;

		p_new_node->data = value;
		p_new_node->p_next = p_head->p_next;

		p_head->p_next = p_new_node;
	}

	template<typename T>
	void add_back(node_t<T>** const pp_head, const T value)
	{
		assert(pp_head != nullptr);

		node_t<T>* const p_new_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));
		assert(p_new_node != nullptr);

		node_t<T>* p_head = *pp_head;

		p_new_node->data = value;
		p_new_node->p_next = p_head->p_next;

		p_head->p_next = p_new_node;

		*pp_head = p_new_node;
	}

	void print_list(const node_t<int>* const p_head)
	{
		assert(p_head != nullptr);

		const node_t<int>* p_node = p_head->p_next;
		while (true) {
			printf("%d ", p_node->data);
			
			p_node = p_node->p_next;

			if (p_node == p_head) {
				break;
			}
		}
		printf("%d\n", p_node->data);
	}
}