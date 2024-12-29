#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "../priority_queue/heap.h"

namespace mst
{
	typedef struct set_array {
		int* p_sets;

		int capacity;
	} set_array_t;

	set_array_t make_set(const int capacity);
	void destroy_set(set_array_t* const p_set_arr);
	int find_set(const set_array_t* const p_set_arr, const int set);
	void union_set(set_array_t* const p_set_arr, const int set_a, const int set_b);

	typedef struct edge {
		int start;
		int end;

		int weight;
	} edge_t;

	typedef struct edge_graph {
		edge_t* p_edges;

		int size;
		int capacity;
	} edge_graph_t;

	edge_graph_t create_edge_graph(const int capacity);
	void destroy_graph(edge_graph_t* const p_this);
	void insert_edge(edge_graph_t* const p_this, const edge_t edge);
	void print_kruskal(const edge_graph_t* const p_graph, const int node_count);

	typedef struct vertex {
		int id;
		int weight;

		struct vertex* p_list;
	} vertex_t;

	typedef struct vertex_graph {
		vertex_t* p_vertices;

		int capacity;
	} vertex_graph_t;

	vertex_graph_t create_vertex_graph(const int capacity);
	void destroy_graph(vertex_graph_t* const p_this);
	void insert_edge(vertex_graph_t* const p_this, const edge_t edge);
	void print_prim(const vertex_graph_t* const p_this, bool is_discovered[]);
}