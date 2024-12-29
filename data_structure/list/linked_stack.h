#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "singly_linked_list.h"

namespace linked_stack
{
	template<typename T>
	using stack_node_t = singly_linked_list::node_t<T>;

	template<typename T>
	struct linked_stack_t {
		stack_node_t<T>* p_top;
	};

	template<typename T>
	linked_stack_t<T> create(const T value)
	{
		stack_node_t<T>* const p_node = singly_linked_list::create_singly_node_malloc(value);

		linked_stack_t<T> ret;
		ret.p_top = p_node;

		return ret;
	}

	template<typename T>
	void destroy(linked_stack_t<T>* const p_linked_stack)
	{
		assert(p_linked_stack != nullptr);

		singly_linked_list::destroy(&(p_linked_stack->p_top));
	}

	template<typename T>
	void push(linked_stack_t<T>* const p_linked_stack, const T value)
	{
		assert(p_linked_stack != nullptr);

		singly_linked_list::add_front(&(p_linked_stack->p_top), value);
	}

	template<typename T>
	T pop(linked_stack_t<T>* const p_linked_stack)
	{
		assert(p_linked_stack != nullptr);

		const T retValue = p_linked_stack->p_top->data;

		singly_linked_list::remove_item(&(p_linked_stack->p_top), retValue);

		return retValue;
	}

	template<typename T>
	T peek(const linked_stack_t<T>* const p_linked_stack)
	{
		assert(p_linked_stack != nullptr);

		return p_linked_stack->p_top->data;
	}
}