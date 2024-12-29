#include "polynomial.h"

polynomial::polynomial_t polynomial::add(const polynomial_t* const lhs, const polynomial_t* const rhs)
{
	assert(lhs != nullptr);
	assert(rhs != nullptr);

	const int lhs_degree = lhs->degree;
	const int rhs_degree = rhs->degree;

	const int result_degree = lhs_degree > rhs_degree ? lhs_degree : rhs_degree;

	polynomial_t result = { result_degree, };

	int lhs_index = lhs_degree;
	int rhs_index = rhs_degree;
	int result_index = result_degree;
	while (lhs_index >= 0 && rhs_index >= 0) {
		result.coefficients[result_index] = lhs->coefficients[lhs_index] + rhs->coefficients[rhs_index];

		--lhs_index;
		--rhs_index;
		--result_index;
	}

	while (lhs_index >= 0) {
		assert(result_index >= 0);
		result.coefficients[result_index] = lhs->coefficients[lhs_index];

		--lhs_index;
		--result_index;
	}

	while (rhs_index >= 0) {
		assert(result_index >= 0);
		result.coefficients[result_index] = rhs->coefficients[rhs_index];

		--rhs_index;
		--result_index;
	}

	return result;
}

void polynomial::print(const polynomial_t* __restrict const poly)
{
	int i;
	for (i = 0; i < poly->degree; ++i) {

		if (abs(poly->coefficients[i] - 0.f) < FLT_EPSILON) {
			continue;
		}

		printf("%.fx^%d + ", poly->coefficients[i], poly->degree - i);
	}

	if (abs(poly->coefficients[i] - 0.f) >= FLT_EPSILON) {
		printf("%.f", poly->coefficients[i]);
	}
	printf("\n");
}

static polynomial::term::polynomial_term_t s_terms[polynomial::MAX_DEGREE + 1] = {
	{ 8, 3 }, { 7, 1 }, { 1, 0 }, { 10, 3 }, { 3, 2 }, { 1, 0 }
};

static int s_avail = 6;

void polynomial::term::attach(const float coefficient, const int exp)
{
	assert(s_avail < MAX_DEGREE + 1);

	s_terms[s_avail++] = { coefficient, exp };
}


void polynomial::term::add(
	const int lhs_start, const int lhs_end,
	const int rhs_start, const int rhs_end,
	int* __restrict p_out_result_start, int* __restrict p_out_result_end
) {
	assert(p_out_result_start != nullptr);
	assert(p_out_result_end != nullptr);

	*p_out_result_start = s_avail;

	int lhs_index = lhs_start;
	int rhs_index = rhs_start;

	float temp_coef = 0;
	while (lhs_index <= lhs_end && rhs_index <= rhs_end) {
		const int lhs_exp = s_terms[lhs_index].exp;
		const int rhs_exp = s_terms[rhs_index].exp;
		if (lhs_exp > rhs_exp) {
			attach(s_terms[lhs_index].coefficient, s_terms[lhs_index].exp);
			++lhs_index;
		}
		else if (lhs_exp == rhs_exp) {
			temp_coef = s_terms[lhs_index].coefficient + s_terms[rhs_index].coefficient;

			if (abs(temp_coef - 0.f) >= FLT_EPSILON) {
				attach(temp_coef, lhs_exp);
			}

			++lhs_index;
			++rhs_index;
		}
		else {
			attach(s_terms[rhs_index].coefficient, s_terms[rhs_index].exp);
			++rhs_index;
		}
	}

	while (lhs_index <= lhs_end) {
		attach(s_terms[lhs_index].coefficient, s_terms[lhs_index].exp);
		++lhs_index;
	}

	while (rhs_index <= rhs_end) {
		attach(s_terms[rhs_index].coefficient, s_terms[rhs_index].exp);
		++rhs_index;
	}

	*p_out_result_end = s_avail - 1;
}

void polynomial::term::print(const int start, const int end)
{
	assert(start < s_avail);
	assert(end < s_avail);
	assert(start <= end);

	int i;
	for (i = start; i < end; ++i) {

		if (abs(s_terms[i].coefficient - 0.f) < FLT_EPSILON) {
			continue;
		}

		printf("%.fx^%d + ", s_terms[i].coefficient, s_terms[i].exp);
	}

	if (s_terms[i].exp == 0) {
		printf("%.f", s_terms[i].coefficient);
	}
	else {
		printf("%.fx^%d", s_terms[i].coefficient, s_terms[i].exp);
	}
	printf("\n");
}
