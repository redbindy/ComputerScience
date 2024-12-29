#include <cstdio>

#include "heap.h"

namespace heap_application
{
	typedef struct machine {
		int id;
		int processing_time;
	} machine_t;

	typedef struct huffman_node {

		int freq;
		char ch;

		struct huffman_node* p_left;
		struct huffman_node* p_right;

	} huffman_node_t;

	void schedule_lpt();
	void encode_huffman_tree(const int freq[], const char ch_list[], const int len);
}