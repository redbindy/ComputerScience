#include "heap_application.h"

static int compare_machine(const heap_application::machine_t a, const heap_application::machine_t b)
{
	return a.processing_time - b.processing_time;
}

void heap_application::schedule_lpt()
{
	using namespace heap;

	constexpr int JOBS = 7;
	constexpr int MACHINES = 3;

	const int jobs[] = { 8, 7, 6, 5, 3, 2, 1 };
	machine_t m = { 0, 0 };

	heap_t<machine_t> heap = create_heap<machine_t>(JOBS);
	{
		for (int i = 0; i < MACHINES; ++i) {
			add(&heap, m, compare_machine);
			++m.id;
		}

		for (int i = 0; i < JOBS; ++i) {
			m = poll(&heap, compare_machine);

			printf("JOB %d을 시간=%d부터 시간=%d까지 기계 %d번에 할당한다. \n", i, m.processing_time, m.processing_time + jobs[i] - 1, m.id);

			m.processing_time += jobs[i];

			add(&heap, m, compare_machine);
		}
	}
	delete_heap(&heap);
}

static int compare_huffman_node(heap_application::huffman_node_t* a, heap_application::huffman_node_t* b)
{
	return a->freq - b->freq;
}

static void destroy_huffman_tree(heap_application::huffman_node_t** const pp_node_or_null)
{
	assert(pp_node_or_null != nullptr);

	if (*pp_node_or_null == nullptr) {
		return;
	}

	destroy_huffman_tree(&((*pp_node_or_null)->p_left));
	destroy_huffman_tree(&((*pp_node_or_null)->p_right));

	free(*pp_node_or_null);

	*pp_node_or_null = nullptr;
}

static void print_huffman_code_recursive(const heap_application::huffman_node_t* const p_node_or_null, char code_str[], const int code_index)
{
	if (p_node_or_null == nullptr) {
		return;
	}

	if (p_node_or_null->p_left == nullptr && p_node_or_null->p_right == nullptr) {
		printf("%c -> %s\n", p_node_or_null->ch, code_str);

		return;
	}

	code_str[code_index] = '1';
	print_huffman_code_recursive(p_node_or_null->p_left, code_str, code_index + 1);

	code_str[code_index] = '0';
	print_huffman_code_recursive(p_node_or_null->p_right, code_str, code_index + 1);

	code_str[code_index] = '\0';
}

void heap_application::encode_huffman_tree(const int freq[], const char ch_list[], const int len)
{
	assert(freq != nullptr);
	assert(ch_list != nullptr);
	assert(len > 0);

	using namespace heap;

	heap_t<huffman_node_t*> heap = create_heap<huffman_node_t*>(len);
	{
		for (int i = 0; i < len; ++i) {
			huffman_node_t* p_node = static_cast<huffman_node_t*>(malloc(sizeof(huffman_node_t)));
			assert(p_node != nullptr);

			p_node->ch = ch_list[i];
			p_node->freq = freq[i];

			p_node->p_left = nullptr;
			p_node->p_right = nullptr;

			add(&heap, p_node, compare_huffman_node);
		}

		huffman_node_t* p_node;
		while (true) {
			p_node = poll(&heap, compare_huffman_node);

			if (is_empty(&heap)) {
				break;
			}

			huffman_node_t* const p_right_node = poll(&heap, compare_huffman_node);

			huffman_node_t* const p_parent = static_cast<huffman_node_t*>(malloc(sizeof(huffman_node_t)));
			assert(p_parent != nullptr);

			p_parent->ch = '\0';
			p_parent->freq = p_node->freq + p_right_node->freq;
			p_parent->p_left = p_node;
			p_parent->p_right = p_right_node;

			add(&heap, p_parent, compare_huffman_node);
		}

		char code[100] = { '\0', };
		print_huffman_code_recursive(p_node, code, 0);

		destroy_huffman_tree(&p_node);
	}
	delete_heap(&heap);
}
