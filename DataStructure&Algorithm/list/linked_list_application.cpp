#include "linked_list_application.h"

using namespace linked_list_application;

term_node_t* linked_list_application::make_term_malloc(const double exp, const double coeff)
{
	term_node_t* const p_node = static_cast<term_node_t*>(malloc(sizeof(term_node_t)));
	assert(p_node != nullptr);

	p_node->exp = exp;
	p_node->coeff = coeff;

	p_node->p_next = nullptr;

	return p_node;
}

void linked_list_application::destroy_polynomial(term_node_t** const pp_term)
{
	assert(pp_term != nullptr);

	term_node_t* p_node = *pp_term;
	while (p_node != nullptr) {
		term_node_t* const p_tmp = p_node;

		p_node = p_node->p_next;

		free(p_tmp);
	}
	*pp_term = nullptr;
}

void linked_list_application::add_polynomial(term_node_t** const pp_poly0, term_node_t* const p_poly1)
{
	assert(pp_poly0 != nullptr);
	assert(*pp_poly0 != nullptr);
	assert(p_poly1 != nullptr);
	assert(abs((*pp_poly0)->exp) >= abs(p_poly1->exp));

	term_node_t* p_lhs = *pp_poly0;
	term_node_t* p_lhs_prev = nullptr;
	term_node_t* p_rhs = p_poly1;

	while (p_lhs != nullptr && p_rhs != nullptr) {
		const double lhs_exp_abs = abs(p_lhs->exp);
		const double rhs_exp_abs = abs(p_rhs->exp);

		if (abs(p_lhs->exp - p_rhs->exp) < DBL_EPSILON) {
			p_lhs->coeff += p_rhs->coeff;

			term_node_t* const p_tmp_rhs = p_rhs;

			p_lhs_prev = p_lhs;
			p_lhs = p_lhs->p_next;
			p_rhs = p_rhs->p_next;

			free(p_tmp_rhs);
		}
		else if (lhs_exp_abs >= rhs_exp_abs) {
			while (p_lhs != nullptr && p_lhs->exp != p_rhs->exp && abs(p_lhs->exp) >= abs(p_rhs->exp)) {
				p_lhs_prev = p_lhs;
				p_lhs = p_lhs->p_next;
			}

			if (p_lhs == nullptr) {
				p_lhs_prev->p_next = p_rhs;
			}
		}
		else {

			while (p_rhs != nullptr && p_lhs->exp != p_rhs->exp && abs(p_lhs->exp) <= abs(p_rhs->exp)) {
				p_lhs_prev->p_next = p_rhs;

				p_lhs_prev = p_lhs_prev->p_next;
				p_rhs = p_rhs->p_next;
			}

			p_lhs_prev->p_next = p_lhs;
		}
	}

	p_lhs = *pp_poly0;
	while (p_lhs != nullptr && abs(p_lhs->coeff - 0.0) < DBL_EPSILON) {
		term_node_t* const p_tmp = p_lhs;

		p_lhs = p_lhs->p_next;

		free(p_tmp);
	}

	*pp_poly0 = p_lhs;

	term_node_t* p_prev = nullptr;
	while (p_lhs != nullptr) {
		term_node_t* p_next = p_lhs->p_next;

		if (abs(p_lhs->coeff - 0.0) < DBL_EPSILON) {
			assert(p_prev != nullptr);

			free(p_lhs);

			p_prev->p_next = p_next;
		}
		else {
			p_prev = p_lhs;
		}

		p_lhs = p_next;
	}
}

static void print_term(const term_node_t* const p_term)
{
	assert(p_term != nullptr);

	const double coeff = p_term->coeff;

	if (coeff < 0) {
		printf("(");
	}

	if (abs(abs(coeff) - 1.0) >= DBL_EPSILON) {
		printf("%.f", coeff);
	}
	else if (abs(coeff + 1.0) < DBL_EPSILON) {
		printf("-");
	}

	const double exp = p_term->exp;

	if (abs(exp - 0.0) < DBL_EPSILON) {

		if (abs(abs(coeff) - 1.0) < DBL_EPSILON) {
			printf("1");
		}

		if (coeff < 0) {
			printf(")");
		}
	}
	else {
		printf("x");

		if (abs(exp - 1.0) >= DBL_EPSILON) {
			printf("^");

			if (exp > 0) {
				printf("%.f", exp);
			}
			else {
				printf("(%.f)", exp);
			}
		}

		if (coeff < 0) {
			printf(")");
		}
	}
}

void linked_list_application::print_polynomial(const term_node_t* const p_term)
{
	assert(p_term != nullptr);

	const term_node_t* p_node = p_term;
	while (p_node->p_next != nullptr) {
		print_term(p_node);

		printf(" + ");

		p_node = p_node->p_next;
	}

	print_term(p_node);
	printf("\n");
}

