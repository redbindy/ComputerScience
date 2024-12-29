#pragma once

#include "singly_linked_list.h"

namespace linked_queue
{
	template<typename T>
	using queue_node_t = singly_linked_list::node_t<T>;

	template<typename T>
	struct linked_queue_t {
		queue_node_t<T>* p_front;
		queue_node_t<T>* p_back;
	};

	template<typename T>
	linked_queue_t<T> create(const T value)
	{
		queue_node_t<T>* p_node = singly_linked_list::create_singly_node_malloc(value);

		linked_queue_t<T> ret;
		ret.p_front = p_node;
		ret.p_back = p_node;

		return ret;
	}

	template<typename T>
	void destroy(linked_queue_t<T>* const p_linked_queue)
	{
		assert(p_linked_queue != nullptr);

		singly_linked_list::destroy(&(p_linked_queue->p_front));
	}

	template<typename T>
	void enqueue(linked_queue_t<T>* const p_linked_queue, const T value)
	{
		assert(p_linked_queue != nullptr);

		queue_node_t<T>* p_new_node = static_cast<queue_node_t<T>*>(malloc(sizeof(queue_node_t<T>)));
		assert(p_new_node != nullptr);

		p_new_node->data = value;
		p_new_node->p_next = nullptr;

		p_linked_queue->p_back->p_next = p_new_node;

		p_linked_queue->p_back = p_new_node;
	}

	template<typename T>
	T dequeue(linked_queue_t<T>* const p_linked_queue)
	{
		assert(p_linked_queue != nullptr);

		const T retValue = p_linked_queue->p_front->data;

		singly_linked_list::remove_item(&(p_linked_queue->p_front), retValue);

		return retValue;
	}

	template<typename T>
	T peek(const linked_queue_t<T>* const p_linked_queue)
	{
		assert(p_linked_queue != nullptr);

		return p_linked_queue->p_front->data;
	}
}