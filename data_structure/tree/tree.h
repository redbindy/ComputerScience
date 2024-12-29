#pragma once

#include "../list/array_list.h"
#include "../list/singly_linked_list.h"

namespace tree
{
	template<typename T>
	struct tree_node_t {
		T data;

		// array_list::array_list_t<tree_node_t<T>*> children;
		singly_linked_list::node_t<tree_node_t<T>*>* p_children_list;
	};
}