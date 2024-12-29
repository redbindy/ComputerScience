#include "mst.h"

namespace mst
{
	static int compare_edge(const void* p_a, const void* p_b)
	{
		assert(p_a != nullptr);
		assert(p_b != nullptr);

		const mst::edge_t* p_e0 = static_cast<const mst::edge_t*>(p_a);
		const mst::edge_t* p_e1 = static_cast<const mst::edge_t*>(p_b);

		return p_e0->weight - p_e1->weight;
	}

	set_array_t mst::make_set(const int capacity)
	{
		assert(capacity > 0);

		const int arr_byte_size = sizeof(int) * capacity;

		set_array_t ret;
		ret.p_sets = static_cast<int*>(malloc(arr_byte_size));
		assert(ret.p_sets != nullptr);

		memset(ret.p_sets, -1, arr_byte_size);

		ret.capacity = capacity;

		return ret;
	}

	void destroy_set(set_array_t* const p_set_arr)
	{
		assert(p_set_arr != nullptr);

		free(p_set_arr->p_sets);

		p_set_arr->p_sets = nullptr;

		p_set_arr->capacity = 0;
	}

	int find_set(const set_array_t* const p_set_arr, const int set)
	{
		assert(p_set_arr != nullptr);
		assert(p_set_arr->p_sets != nullptr);
		assert(set >= 0);
		assert(set < p_set_arr->capacity);

		int curr_set = set;
		while (true) {
			const int parent = p_set_arr->p_sets[curr_set];

			if (parent == -1) {
				break;
			}

			curr_set = parent;
		}

		return curr_set;
	}

	void union_set(set_array_t* const p_set_arr, const int set_a, const int set_b)
	{
		assert(p_set_arr != nullptr);
		assert(p_set_arr->p_sets != nullptr);
		assert(set_a >= 0);
		assert(set_a < p_set_arr->capacity);
		assert(set_b >= 0);
		assert(set_b < p_set_arr->capacity);

		const int parent_a = find_set(p_set_arr, set_a);
		const int parent_b = find_set(p_set_arr, set_b);

		if (parent_a == parent_b) {
			return;
		}

		p_set_arr->p_sets[set_b] = parent_a;
	}

	edge_graph_t create_edge_graph(const int capacity)
	{
		assert(capacity > 0);

		edge_graph_t ret;
		ret.p_edges = static_cast<edge_t*>(malloc(sizeof(edge_t) * capacity));

		ret.size = 0;
		ret.capacity = capacity;

		return ret;
	}

	void destroy_graph(edge_graph_t* const p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_edges);

		p_this->p_edges = nullptr;

		p_this->size = -1;
		p_this->capacity = -1;
	}

	void insert_edge(edge_graph_t* const p_this, const edge_t edge)
	{
		assert(p_this != nullptr);
		assert(p_this->p_edges != nullptr);
		assert(edge.start >= 0);
		assert(edge.end >= 0);

		p_this->p_edges[p_this->size] = edge;

		++p_this->size;
	}

	void mst::print_kruskal(const edge_graph_t* const p_graph, const int node_count)
	{
		assert(p_graph != nullptr);
		assert(p_graph->p_edges != nullptr);
		assert(p_graph->capacity > 0);

		set_array_t sets = make_set(node_count);
		{
			const int edges_byte_size = sizeof(edge_t) * p_graph->size;
			edge_t* p_edges = static_cast<edge_t*>(malloc(edges_byte_size));
			assert(p_edges != nullptr);

			memcpy(p_edges, p_graph->p_edges, edges_byte_size);

			qsort(p_edges, p_graph->size, sizeof(edge_t), compare_edge);

			int edge_count = 0;
			int sum = 0;
			for (const edge_t* p = p_edges; p < p_edges + p_graph->size; ++p) {

				if (edge_count == node_count - 1) {
					break;
				}

				const int start_parent = find_set(&sets, p->start);
				const int end_parent = find_set(&sets, p->end);

				if (start_parent == end_parent) {
					continue;
				}

				union_set(&sets, p->start, p->end);
				++edge_count;

				printf("selected: %d - %d\n", p->start, p->end);

				sum += p->weight;
			}

			printf("MST total: %d\n", sum);
		}
		destroy_set(&sets);
	}

	vertex_graph_t create_vertex_graph(const int capacity)
	{
		assert(capacity > 0);

		vertex_graph_t ret;
		ret.p_vertices = static_cast<vertex_t*>(malloc(sizeof(vertex_t) * capacity));
		assert(ret.p_vertices != nullptr);

		for (int i = capacity - 1; i >= 0; --i) {
			ret.p_vertices[i].id = i;
			ret.p_vertices[i].weight = 0;
			ret.p_vertices[i].p_list = nullptr;
		}
		ret.capacity = capacity;

		return ret;
	}

	void destroy_graph(vertex_graph_t* const p_this)
	{
		assert(p_this != nullptr);

		for (int i = p_this->capacity - 1; i >= 0; --i) {

			vertex_t* p_v = p_this->p_vertices[i].p_list;
			while (p_v != nullptr) {

				vertex_t* p_next = p_v->p_list;

				free(p_v);

				p_v = p_next;
			}
		}

		free(p_this->p_vertices);

		p_this->p_vertices = nullptr;

		p_this->capacity = -1;
	}

	void insert_edge(vertex_graph_t* const p_this, const edge_t edge)
	{
		assert(p_this != nullptr);
		assert(p_this->p_vertices != nullptr);
		assert(edge.start >= 0);
		assert(edge.start < p_this->capacity);
		assert(edge.end >= 0);
		assert(edge.end < p_this->capacity);

		vertex_t* const p_start_vertex = static_cast<vertex_t*>(malloc(sizeof(vertex_t)));
		assert(p_start_vertex != nullptr);

		p_start_vertex->id = edge.start;
		p_start_vertex->weight = edge.weight;

		vertex_t* const p_end_vertex = static_cast<vertex_t*>(malloc(sizeof(vertex_t)));
		assert(p_end_vertex != nullptr);

		p_end_vertex->id = edge.end;
		p_end_vertex->weight = edge.weight;

		vertex_t* const p_start_list = p_this->p_vertices[edge.start].p_list;

		p_end_vertex->p_list = p_start_list;

		p_this->p_vertices[edge.start].p_list = p_end_vertex;

		vertex_t* const p_end_list = p_this->p_vertices[edge.end].p_list;

		p_start_vertex->p_list = p_end_list;

		p_this->p_vertices[edge.end].p_list = p_start_vertex;
	}

	static int compare_vertex(vertex_t* p_a, vertex_t* p_b)
	{
		assert(p_a != nullptr);
		assert(p_b != nullptr);

		return p_a->weight - p_b->weight;
	}

	void print_prim(const vertex_graph_t* const p_this, bool is_discovered[])
	{
		assert(p_this != nullptr);
		assert(p_this->p_vertices != nullptr);

		using namespace heap;

		heap_t<vertex_t*> heap = create_heap<vertex_t*>(p_this->capacity);
		{
			const vertex_t* const p_start = p_this->p_vertices;
			is_discovered[0] = true;

			vertex_t* p_list = p_start->p_list;
			while (p_list != nullptr) {

				add(&heap, p_list, compare_vertex);
				p_list = p_list->p_list;
			}

			int node_count = 1;
			int sum = 0;
			while (node_count != p_this->capacity) {
				vertex_t* p_nearest = poll(&heap, compare_vertex);

				if (is_discovered[p_nearest->id]) {
					continue;
				}

				is_discovered[p_nearest->id] = true;

				++node_count;
				sum += p_nearest->weight;

				printf("selected: %d\n", p_nearest->id);

				p_list = p_this->p_vertices[p_nearest->id].p_list;
				while (p_list != nullptr) {

					add(&heap, p_list, compare_vertex);
					p_list = p_list->p_list;
				}
			}

			printf("MST total: %d\n", sum);
		}
		delete_heap(&heap);
	}
}
