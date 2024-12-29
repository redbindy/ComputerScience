#include "topology_sort.h"

namespace topology_sort
{
	graph_t create_graph(const int capacity)
	{
		assert(capacity > 0);

		graph_t ret;
		ret.pp_adj_list = static_cast<node_t<int>**>(malloc(sizeof(node_t<int>*) * capacity));
		assert(ret.pp_adj_list != nullptr);

		ret.capacity = capacity;

		for (int i = capacity - 1; i >= 0; --i) {
			ret.pp_adj_list[i] = nullptr;
		}

		return ret;
	}

	void destroy_graph(graph_t* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->pp_adj_list != nullptr);

		for (int i = p_this->capacity - 1; i >= 0; --i) {
			destroy(p_this->pp_adj_list + i);
		}

		free(p_this->pp_adj_list);

		p_this->capacity = -1;
	}

	void insert_edge(graph_t* const p_this, const int start, const int end)
	{
		assert(p_this != nullptr);
		assert(p_this->pp_adj_list != nullptr);
		assert(start >= 0);
		assert(start < p_this->capacity);
		assert(end >= 0);
		assert(end < p_this->capacity);

		add_back(p_this->pp_adj_list + start, end);
	}

	void print_topology_sort(const graph_t* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->pp_adj_list != nullptr);

		int* in_degrees = static_cast<int*>(malloc(sizeof(int) * p_this->capacity));
		assert(in_degrees != nullptr);
		{
			memset(in_degrees, 0, sizeof(int) * p_this->capacity);

			for (int i = p_this->capacity - 1; i >= 0; --i) {

				node_t<int>* p_node = p_this->pp_adj_list[i];
				while (p_node != nullptr) {
					++in_degrees[p_node->data];

					p_node = p_node->p_next;
				}
			}

			stack_t<int> stack = create<int>(p_this->capacity);
			for (int i = 0; i < p_this->capacity; ++i) {
				
				if (in_degrees[i] == 0) {
					push(&stack, i);
				}
			}

			while (!is_empty(&stack)) {

				const int v = pop(&stack);

				printf("%d -> ", v);

				node_t<int>* p_node = p_this->pp_adj_list[v];
				while (p_node != nullptr) {
					const int next_v = p_node->data;

					--in_degrees[next_v];

					if (in_degrees[next_v] == 0) {
						push(&stack, next_v);
					}

					p_node = p_node->p_next;
				}
			}
		}
		free(in_degrees);
	}
}
