#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>

namespace recursion
{
	uint32_t get_factorial_recursive(const uint32_t n);
	uint32_t get_factorial_tail_recursive(const uint32_t n);
	uint32_t get_factorial_tail_recursive(const uint32_t n, const uint32_t curr);
	uint32_t get_factorial(const uint32_t n);

	double get_power(const double coeff, const uint32_t exp);
	double get_power_recursive(const double coeff, const uint32_t exp);

	uint32_t get_fibonacci_recursive(const uint32_t n);
	uint32_t get_fibonacci_tail_recursive(const uint32_t n);
	uint32_t get_fibonacci_tail_recursive(const uint32_t n, const uint32_t prev, const uint32_t curr);
	uint32_t get_fibonacci(const uint32_t n);

	void solve_hanoi_recursive(const uint32_t n);
	void solve_hanoi_recursive(const uint32_t n, const uint32_t from, const uint32_t temp, const uint32_t to);

	uint32_t get_binomial_coefficient_recursive(const uint32_t n, const uint32_t k);
	uint32_t get_binomial_coefficient(const uint32_t n, const uint32_t k);
}