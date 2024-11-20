#pragma once

#include <cassert>
#include <cstdio>
#include <cfloat>
#include <cmath>

enum {
	MAX_DEGREE = 100
};

typedef struct polynomial {
	int degree;
	float coefficients[MAX_DEGREE + 1];
} polynomial_t;

polynomial_t polynomial_add(const polynomial_t* lhs, const polynomial_t* rhs);
void polynomial_print(const polynomial_t* __restrict poly);

typedef struct polynomial_term {
	float coefficient;
	int exponent;
} polynomial_term_t;

void polynomial_term_attach(const float coefficient, const int exponent);

void polynomial_term_add(
	const int lhs_start, const int lhs_end,
	const int rhs_start, const int rhs_end,
	int* __restrict p_out_result_start, int* __restrict p_out_result_end
);

void polynomial_term_print(const int start, const int end);