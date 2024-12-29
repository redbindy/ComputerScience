#include "singly_linked_list.h"

void singly_linked_list::print_list(const node_t<int>* const p_head)
{
	const node_t<int>* p_node = p_head;
	while (p_node != nullptr) {
		printf("%d ", p_node->data);

		p_node = p_node->p_next;
	}
	printf("\n");
}
