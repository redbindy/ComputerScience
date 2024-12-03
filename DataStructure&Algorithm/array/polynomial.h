#pragma once

#include <cassert>
#include <cstdio>
#include <cfloat>
#include <cmath>

namespace polynomial
{
	enum {
		MAX_DEGREE = 100
	};

	typedef struct {
		int degree;
		float coefficients[MAX_DEGREE + 1];
	} polynomial_t;

	polynomial_t add(const polynomial_t* lhs, const polynomial_t* rhs);
	void print(const polynomial_t* __restrict poly);

	namespace term
	{
		typedef struct {
			float coefficient;
			int exponent;
		} polynomial_term_t;

		void attach(const float coefficient, const int exponent);

		void add(
			const int lhs_start, const int lhs_end,
			const int rhs_start, const int rhs_end,
			int* __restrict p_out_result_start, int* __restrict p_out_result_end
		);

		void print(const int start, const int end);
	}
}