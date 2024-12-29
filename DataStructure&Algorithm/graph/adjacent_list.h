#pragma once

#include <cassert>
#include <cstring>

#include "../list/singly_linked_list.h"
#include "../stack/stack.h"
#include "../queue/ring_queue.h"

namespace adjacent_list
{
	using namespace singly_linked_list;

	typedef struct graph {
		node_t<int>** pp_nodes;

		int capacity;
		int size;
	} graph_t;

	graph_t create_graph(const int capacity)
	{
		assert(capacity > 0);

		const int list_byte_size = sizeof(node_t<int>*) * capacity;

		graph_t ret;
		ret.pp_nodes = static_cast<node_t<int>**>(malloc(list_byte_size));
		assert(ret.pp_nodes != nullptr);

		memset(ret.pp_nodes, 0, list_byte_size);

		ret.capacity = capacity;
		ret.size = 0;

		return ret;
	}

	void destroy_graph(graph_t* const p_this)
	{
		assert(p_this != nullptr);

		for (int i = p_this->capacity - 1; i >= 0; --i) {
			singly_linked_list::destroy(p_this->pp_nodes + i);
		}

		free(p_this->pp_nodes);

		p_this->capacity = -1;
		p_this->size = -1;
	}

	bool is_empty(const graph_t* const p_this)
	{
		assert(p_this != nullptr);

		return p_this->size == 0;
	}

	void insert_vertex(graph_t* const p_this, const int v)
	{
		assert(p_this != nullptr);
		assert(v >= 0);
		assert(v < p_this->capacity);

		++p_this->size;

		p_this->pp_nodes[v] = create_singly_node_malloc(v);
	}

	void insert_edge(graph_t* const p_this, const int start, const int end)
	{
		assert(p_this != nullptr);
		assert(start >= 0);
		assert(end >= 0);
		assert(start < p_this->size);
		assert(end < p_this->size);

		if (p_this->pp_nodes[start] == nullptr) {
			insert_vertex(p_this, start);
		}

		if (p_this->pp_nodes[end] == nullptr) {
			insert_vertex(p_this, end);
		}

		add_back(p_this->pp_nodes + start, end);
		add_back(p_this->pp_nodes + end, start);
	}

	void delete_vertex(graph_t* const p_this, const int v)
	{
		assert(p_this != nullptr);
		assert(v >= 0);
		assert(v < p_this->size);

		singly_linked_list::destroy(p_this->pp_nodes + v);
	}

	void delete_edge(graph_t* const p_this, const int start, const int end)
	{
		assert(p_this != nullptr);
		assert(start >= 0);
		assert(end >= 0);
		assert(start < p_this->size);
		assert(end < p_this->size);

		remove_item(p_this->pp_nodes + start, end);
		remove_item(p_this->pp_nodes + end, start);
	}

	void print_adjacent(const graph_t* const p_this, const int v)
	{
		assert(p_this != nullptr);
		assert(v >= 0);
		assert(v < p_this->size);

		printf("adjacent: ");
		for (const node_t<int>* p = p_this->pp_nodes[v]->p_next; p != nullptr; p = p->p_next) {
			printf("%d -> ", p->data);
		}
		printf("\n");
	}

	void print_adjacent_list(const graph_t* const p_this)
	{
		assert(p_this != nullptr);

		printf("----------\n");
		for (int i = 0; i < p_this->capacity; ++i) {

			if (p_this->pp_nodes[i] == nullptr) {
				continue;
			}

			printf("%d ", p_this->pp_nodes[i]->data);

			print_adjacent(p_this, i);
		}
		printf("----------\n");
	}

	void print_dfs_recursive(const graph_t* const p_this, const node_t<int>* const p_node_or_null, bool is_discovered[])
	{
		assert(p_this != nullptr);

		if (p_node_or_null == nullptr || is_discovered[p_node_or_null->data])
		{
			return;
		}

		const node_t<int>* p = p_node_or_null;
		is_discovered[p->data] = true;

		printf("%d -> ", p->data);

		while (true) {
			
			p = p->p_next;

			if (p == nullptr) {
				break;
			}

			print_dfs_recursive(p_this, p_this->pp_nodes[p->data], is_discovered);
		}
	}

	void print_dfs(const graph_t* const p_this, bool is_discovered[])
	{
		assert(p_this != nullptr);

		using namespace stack;

		stack_t<node_t<int>*> stack = create<node_t<int>*>(p_this->size);
		{
			node_t<int>* p_node = p_this->pp_nodes[0];

			push(&stack, p_node);
			is_discovered[p_node->data] = true;

			while (!is_empty(&stack)) {

				p_node = pop(&stack);

				printf("%d -> ", p_node->data);

				node_t<int>* p_neighbor = p_node->p_next;
				while (p_neighbor != nullptr) {

					if (!is_discovered[p_neighbor->data]) {

						is_discovered[p_neighbor->data] = true;
						push(&stack, p_this->pp_nodes[p_neighbor->data]);
					}

					p_neighbor = p_neighbor->p_next;
				}
			}
		}
		delete_stack(&stack);
	}

	void print_bfs(const graph_t* const p_this, bool is_discovered[])
	{
		assert(p_this != nullptr);

		using namespace ring_queue;

		ring_queue_t<node_t<int>*> queue = create<node_t<int>*>(p_this->size);
		{
			node_t<int>* p_node = p_this->pp_nodes[0];

			enqueue(&queue, p_node);
			is_discovered[p_node->data] = true;

			while (!is_empty(&queue)) {

				p_node = dequeue(&queue);

				printf("%d -> ", p_node->data);

				node_t<int>* p_neighbor = p_node->p_next;
				while (p_neighbor != nullptr) {

					if (!is_discovered[p_neighbor->data]) {

						is_discovered[p_neighbor->data] = true;
						enqueue(&queue, p_this->pp_nodes[p_neighbor->data]);
					}

					p_neighbor = p_neighbor->p_next;
				}
			}
		}
		delete_ring_queue(&queue);
	}
}