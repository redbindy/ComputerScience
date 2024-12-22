#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <cfloat>

#include "array_list.h"

namespace linked_list_application
{
	typedef struct term_node {
		double exp;
		double coeff;

		struct term_node* p_next;
	} term_node_t;

	term_node_t* make_term_malloc(const double exp, const double coeff);
	void destroy_polynomial(term_node_t** const pp_term);
	void add_polynomial(term_node_t** const pp_poly0, term_node_t* const p_poly1);
	void print_polynomial(const term_node_t* const p_term);
}