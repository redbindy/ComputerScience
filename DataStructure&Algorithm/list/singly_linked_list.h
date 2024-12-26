#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>

namespace singly_linked_list
{
	template<typename T>
	struct node_t {
		T data;

		node_t* p_next;
	};

	template<typename T>
	node_t<T>* create_singly_node_malloc(const T value)
	{
		node_t<T>* const p_node = static_cast<node_t<T>*>(malloc(sizeof(node_t<T>)));
		assert(p_node != nullptr);

		p_node->data = value;

		p_node->p_next = nullptr;

		return p_node;
	}

	template<typename T>
	void destroy(node_t<T>** const pp_head)
	{
		assert(pp_head != nullptr);

		node_t<T>* p_head = *pp_head;
		while (p_head != nullptr) {
			node_t<T>* p_next = p_head->p_next;

			free(p_head);

			p_head = p_next;
		}

		*pp_head = nullptr;
	}

	template<typename T>
	void destroy_recursive(node_t<T>** const pp_head)
	{
		assert(pp_head != nullptr);

		if (*pp_head == nullptr) {
			return;
		}

		destroy_recursive(&((*pp_head)->p_next));

		free(*pp_head);
		*pp_head = nullptr;
	}

	template<typename T>
	void add_front(node_t<T>** const pp_head, const int value)
	{
		assert(pp_head != nullptr);

		node_t<T>* const p_new_node = create_singly_node_malloc(value);
		p_new_node->p_next = *pp_head;

		*pp_head = p_new_node;
	}

	template<typename T>
	void add_back(node_t<T>** const pp_head, const int value)
	{
		assert(pp_head != nullptr);

		node_t<T>* const p_new_node = create_singly_node_malloc(value);
		p_new_node->p_next = nullptr;

		node_t<T>** pp_node = pp_head;
		while (*pp_node != nullptr) {
			pp_node = &((*pp_node)->p_next);
		}

		*pp_node = p_new_node;
	}

	template<typename T>
	void add_sorted(node_t<T>** const pp_head, const int value)
	{
		assert(pp_head != nullptr);

		node_t<T>* const p_new_node = create_singly_node_malloc(value);
		p_new_node->p_next = nullptr;

		node_t<T>** pp_node = pp_head;
		while (*pp_node != nullptr) {
			if ((*pp_node)->data >= value) {
				break;
			}

			pp_node = &((*pp_node)->p_next);
		}
		p_new_node->p_next = *pp_node;
		*pp_node = p_new_node;
	}

	template<typename T>
	node_t<T>* add_last_recursive(node_t<T>* const p_head_or_null, const int value)
	{
		if (p_head_or_null == nullptr) {
			return create_singly_node_malloc(value);
		}

		p_head_or_null->p_next = add_last_recursive(p_head_or_null->p_next, value);

		return p_head_or_null;
	}

	template<typename T>
	void remove_item(node_t<T>** const pp_head, const int value)
	{
		assert(pp_head != nullptr);

		node_t<T>** pp_node = pp_head;
		while (*pp_node != nullptr) {
			if ((*pp_node)->data == value) {
				node_t<T>* const p_tmp = *pp_node;

				*pp_node = (*pp_node)->p_next;

				free(p_tmp);

				break;
			}

			pp_node = &((*pp_node)->p_next);
		}
	}

	template<typename T>
	node_t<T>* remove_item_recursive(node_t<T>* const p_head_or_null, const int value)
	{
		if (p_head_or_null == nullptr) {
			return nullptr;
		}

		if (p_head_or_null->data == value) {
			node_t<T>* p_next = p_head_or_null->p_next;

			free(p_head_or_null);

			return p_next;
		}

		p_head_or_null->p_next = remove_item_recursive(p_head_or_null->p_next, value);

		return p_head_or_null;
	}

	template<typename T>
	void reverse_list(node_t<T>** const pp_head)
	{
		assert(pp_head != nullptr);

		node_t<T>* p_prev = nullptr;
		node_t<T>* p_node = *pp_head;
		while (p_node != nullptr) {
			node_t<T>* p_next = p_node->p_next;
			p_node->p_next = p_prev;

			p_prev = p_node;
			p_node = p_next;
		}
		*pp_head = p_prev;
	}

	template<typename T>
	node_t<T>* reverse_list_recursive(node_t<T>* const p_prev, node_t<T>* const p_node_or_null)
	{
		if (p_node_or_null == nullptr)
		{
			return p_prev;
		}

		node_t<T>* ret = reverse_list_recursive(p_node_or_null, p_node_or_null->p_next);

		p_node_or_null->p_next = p_prev;

		return ret;
	}

	template<typename T>
	void interleave_recursive(node_t<T>* const p_front_or_null, node_t<T>* const p_back_or_null)
	{
		if (p_front_or_null == nullptr || p_back_or_null == nullptr)
		{
			return;
		}

		node_t<T>* p_next = p_front_or_null->p_next;

		p_front_or_null->p_next = p_back_or_null;
		interleave_recursive(p_back_or_null, p_next);
	}

	template<typename T>
	void interleave(node_t<T>* const p_front, node_t<T>* const p_back)
	{
		node_t<T>* p_frt = p_front;
		node_t<T>* p_bck = p_back;
		while (p_frt != nullptr && p_bck != nullptr) {
			node_t<T>* p_next = p_frt->p_next;

			p_frt->p_next = p_bck;

			p_frt = p_bck;
			p_bck = p_next;
		}
	}

	void print_list(const node_t<int>* const p_head)
	{
		const node_t<int>* p_node = p_head;
		while (p_node != nullptr) {
			printf("%d ", p_node->data);

			p_node = p_node->p_next;
		}
		printf("\n");
	}
}