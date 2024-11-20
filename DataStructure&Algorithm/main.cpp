#include <cstdio>
#include <cassert>
#include <cmath>
#include <float.h>

#include "./recursion/recursion.h"

void test_recursion();

int main(void)
{
	test_recursion();

	return 0;
}

void test_recursion()
{
	// factorial
	{
		uint32_t n = 0;
		uint32_t expected = 1;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_tail_recursive(n) == expected);
		assert(get_factorial(n) == expected);

		n = 1;
		expected = 1;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_tail_recursive(n) == expected);
		assert(get_factorial(n) == expected);

		n = 2;
		expected = 2;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_tail_recursive(n) == expected);
		assert(get_factorial(n) == expected);

		n = 10;
		expected = 3'628'800;
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial_recursive(n) == expected);
		assert(get_factorial(n) == expected);
	}

	// power
	{
		double base = 2;
		uint32_t exponent = 0;
		double expected = 1;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 1;
		expected = 2;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 10;
		expected = 1024;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		base = 3;
		exponent = 0;
		expected = 1;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 1;
		expected = 3;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);

		exponent = 5;
		expected = 243;
		assert(abs(get_power(base, exponent) - expected) <= DBL_EPSILON);
		assert(abs(get_power_recursive(base, exponent) - expected) <= DBL_EPSILON);
	}

	// fibonacci
	{
		uint32_t n = 0;
		uint32_t expected = 0;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);

		n = 1;
		expected = 1;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);

		n = 2;
		expected = 1;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);

		n = 16;
		expected = 987;
		assert(get_fibonacci_recursive(n) == expected);
		assert(get_fibonacci_tail_recursive(n) == expected);
		assert(get_fibonacci(n) == expected);
	}

	// Hanoi
	{
		solve_hanoi_recursive(6);
	}

	// binomial coefficient
	{
		uint32_t n = 1;
		uint32_t k = 0;
		uint32_t expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		k = 1;
		expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 3;
		k = 0;
		expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 3;
		k = 3;
		expected = 1;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 3;
		k = 1;
		expected = 3;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);

		n = 10;
		k = 5;
		expected = 252;
		assert(get_binomial_coefficient_recursive(n, k) == expected);
		assert(get_binomial_coefficient(n, k) == expected);
	}
}
