#include "shortest_path.h"

namespace shortest_path
{
	list_graph_t create_list_graph(const int capacity)
	{
		assert(capacity > 0);

		list_graph_t ret;
		ret.pp_adj_list = static_cast<node_t<element>**>(malloc(sizeof(node_t<element>*) * capacity));

		for (node_t<element>** pp = ret.pp_adj_list; pp < ret.pp_adj_list + capacity; ++pp) {
			*pp = nullptr;
		}

		ret.capacity = capacity;

		return ret;
	}

	void destroy_graph(list_graph_t* const p_this)
	{
		assert(p_this != nullptr);

		for (int i = p_this->capacity - 1; i >= 0; --i) {
			destroy(p_this->pp_adj_list + i);
		}

		free(p_this->pp_adj_list);

		p_this->capacity = -1;
	}

	static inline int convert_to_index(const int r, const int c, const int capacity)
	{
		assert(r >= 0);
		assert(r < capacity);
		assert(c >= 0);
		assert(r < capacity);
		assert(capacity >= 0);

		return r * capacity + c;
	}

	matrix_graph_t create_matrix_graph(const int capacity)
	{
		assert(capacity > 0);

		matrix_graph_t ret;

		ret.p_weight_matrix = static_cast<int*>(malloc(sizeof(int) * capacity * capacity));
		assert(ret.p_weight_matrix != nullptr);

		for (int r = capacity - 1; r >= 0; --r) {
			for (int c = capacity - 1; c >= 0; --c) {
				ret.p_weight_matrix[convert_to_index(r, c, capacity)] = INF;
			}
		}

		for (int i = capacity - 1; i >= 0; --i) {
			ret.p_weight_matrix[convert_to_index(i, i, capacity)] = 0;
		}

		ret.capacity = capacity;

		return ret;
	}

	void destroy_graph(matrix_graph_t* const p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_weight_matrix);

		p_this->capacity = -1;
	}

	void insert_edge(list_graph_t* const p_this, const int start, const int end, const int weight)
	{
		assert(p_this != nullptr);
		assert(p_this->pp_adj_list != nullptr);
		assert(start >= 0);
		assert(start < p_this->capacity);
		assert(end >= 0);
		assert(end < p_this->capacity);
		assert(weight >= 0);

		element_t start_e = { start, weight };
		element_t end_e = { end, weight };

		add_front(p_this->pp_adj_list + start, end_e);
		add_front(p_this->pp_adj_list + end, start_e);
	}

	void insert_edge(matrix_graph_t* const p_this, const int start, const int end, const int weight)
	{
		assert(p_this != nullptr);
		assert(p_this->p_weight_matrix != nullptr);
		assert(start >= 0);
		assert(start < p_this->capacity);
		assert(end >= 0);
		assert(end < p_this->capacity);
		assert(weight >= 0);

		p_this->p_weight_matrix[convert_to_index(start, end, p_this->capacity)] = weight;
		p_this->p_weight_matrix[convert_to_index(end, start, p_this->capacity)] = weight;
	}

	static void print_distances(const int* const p_distance, const int len)
	{
		assert(p_distance != nullptr);

		printf("distance: ");
		for (const int* p = p_distance; p < p_distance + len; ++p) {
			
			if (*p != INF) {
				printf("%d ", *p);
			}
			else {
				printf("* ");
			}
		}
		printf("\n");
	}

	static int compare_element(const element_t e0, const element_t e1)
	{
		assert(e0.id >= 0);
		assert(e1.id >= 0);
		assert(e0.weight >= 0);
		assert(e1.weight >= 0);

		return e0.weight - e1.weight;
	}

	void print_dijkstra(const list_graph_t* const p_this, const int start)
	{
		assert(p_this != nullptr);
		assert(p_this->pp_adj_list != nullptr);

		int* p_distance = static_cast<int*>(malloc(sizeof(int) * p_this->capacity));
		assert(p_distance != nullptr);

		heap_t<element_t> heap = create_heap<element_t>(p_this->capacity);
		{
			for (int* p = p_distance; p < p_distance + p_this->capacity; ++p) {
				*p = INF;
			}
			p_distance[start] = 0;

			add(&heap, { start, 0 }, compare_element);
			while (!is_empty(&heap)) {

				element_t e = poll(&heap, compare_element);

				if (e.weight > p_distance[e.id]) {
					continue;
				}

				node_t<element_t>* p_node = p_this->pp_adj_list[e.id];
				while (p_node != nullptr) {
					element_t next_e = p_node->data;

					const int next_dist = p_distance[e.id] + next_e.weight;
					if (next_dist < p_distance[next_e.id]) {
						p_distance[next_e.id] = next_dist;
						next_e.weight = next_dist;

						add(&heap, next_e, compare_element);
					}

					p_node = p_node->p_next;
				}

				print_distances(p_distance, p_this->capacity);
			}
		}
		delete_heap(&heap);
		free(p_distance);
	}

	void print_dijkstra(const matrix_graph_t* const p_this, const int start)
	{
		assert(p_this != nullptr);
		assert(p_this->p_weight_matrix != nullptr);

		int* p_distance = static_cast<int*>(malloc(sizeof(int) * p_this->capacity));
		assert(p_distance != nullptr);

		bool* p_is_visited = static_cast<bool*>(malloc(sizeof(bool) * p_this->capacity));
		assert(p_is_visited != nullptr);

		memset(p_is_visited, false, sizeof(bool) * p_this->capacity);
		{
			for (int* p = p_distance; p < p_distance + p_this->capacity; ++p) {
				*p = INF;
			}
			p_distance[start] = 0;

			for (int count = 0; count < p_this->capacity; ++count) {

				int i;
				for (i = 0; i < p_this->capacity; ++i) {

					if (!p_is_visited[i]) {
						break;
					}
				}

				int min_index = i;
				for (i = 0; i < p_this->capacity; ++i) {

					if (!p_is_visited[i] && p_distance[i] < p_distance[min_index]) {
						min_index = i;
					}
				}

				assert(min_index < p_this->capacity);
				p_is_visited[min_index] = true;

				for (int i = 0; i < p_this->capacity; ++i) {

					const int new_distance = p_distance[min_index] + p_this->p_weight_matrix[convert_to_index(min_index, i, p_this->capacity)];
					if (new_distance < p_distance[i]) {
						p_distance[i] = new_distance;
					}
				}

				print_distances(p_distance, p_this->capacity);
			}
		}
		free(p_distance);
	}

	static void print_weight_matrix(const int* const p_weight_matrix, const int n)
	{
		printf("---------------\n");
		for (int y = 0; y < n; ++y) {
			for (int x = 0; x < n; ++x) {

				const int value = p_weight_matrix[convert_to_index(y, x, n)];

				if (value != INF) {
					printf("%d ", value);
				}
				else {
					printf("* ");
				}
			}
			printf("\n");
		}
		printf("---------------\n");
	}

	void print_floyd(const matrix_graph_t* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_weight_matrix != nullptr);

		matrix_graph_t graph = create_matrix_graph(p_this->capacity);
		{
			memcpy(graph.p_weight_matrix, p_this->p_weight_matrix, sizeof(int) * p_this->capacity * p_this->capacity);

			for (int r = 0; r < graph.capacity; ++r) {

				print_weight_matrix(graph.p_weight_matrix, graph.capacity);

				for (int c = 0; c < graph.capacity; ++c) {
					for (int k = 0; k < graph.capacity; ++k) {

						const int new_dist = graph.p_weight_matrix[convert_to_index(r, k, p_this->capacity)] 
							+ graph.p_weight_matrix[convert_to_index(k, c, p_this->capacity)];

						if (new_dist < graph.p_weight_matrix[convert_to_index(r, c, p_this->capacity)]) {
							graph.p_weight_matrix[convert_to_index(r, c, p_this->capacity)] = new_dist;
						}
					}
				}
			}

			print_weight_matrix(graph.p_weight_matrix, graph.capacity);
		}
		destroy_graph(&graph);
	}
}
