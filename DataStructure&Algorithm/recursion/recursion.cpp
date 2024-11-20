#include "recursion.h"

uint32_t get_factorial_recursive(const uint32_t n)
{
	if (n <= 1) {
		return 1;
	}

	return n * get_factorial_recursive(n - 1);
}

uint32_t get_factorial_tail_recursive(const uint32_t n)
{
	return get_factorial_tail_recursive(n, 1);
}

uint32_t get_factorial_tail_recursive(const uint32_t n, const uint32_t curr)
{
	if (n <= 1) {
		return curr;
	}

	return get_factorial_tail_recursive(n - 1, curr * n);
}

uint32_t get_factorial(const uint32_t n)
{
	int result = 1;
	for (int i = n; i > 0; --i) {
		result *= i;
	}

	return result;
}

double get_power(const double base, const uint32_t exponent)
{
	double result = 1;
	for (int i = 0; i < exponent; ++i)
	{
		result *= base;
	}

	return result;
}

double get_power_recursive(const double base, const uint32_t exponent)
{
	if (exponent == 0)
	{
		return 1;
	}

	if (exponent % 2 == 0)
	{
		return get_power_recursive(base * base, exponent / 2);
	}

	return base * get_power_recursive(base * base, (exponent - 1) / 2);
}

uint32_t get_fibonacci_recursive(const uint32_t n)
{
	if (n <= 1)
	{
		return n;
	}

	return get_fibonacci_recursive(n - 1) + get_fibonacci_recursive(n - 2);
}

uint32_t get_fibonacci_tail_recursive(const uint32_t n)
{
	return get_fibonacci_tail_recursive(n, 0, 1);
}

uint32_t get_fibonacci_tail_recursive(const uint32_t n, const uint32_t prev, const uint32_t curr)
{
	if (n == 0)
	{
		return prev;
	}

	if (n == 1)
	{
		return curr;
	}

	return get_fibonacci_tail_recursive(n - 1, curr, curr + prev);
}

uint32_t get_fibonacci(const uint32_t n)
{
	if (n <= 1)
	{
		return n;
	}

	uint32_t prev = 0;
	uint32_t curr = 1;

	for (int i = n; i > 1; --i)
	{
		const uint32_t next = curr + prev;

		prev = curr;
		curr = next;
	}

	return curr;
}

void solve_hanoi_recursive(const uint32_t n)
{
	assert(n > 0);

	solve_hanoi_recursive(n, 0, 1, 2);
}

void solve_hanoi_recursive(const uint32_t n, const uint32_t from, const uint32_t temp, const uint32_t to)
{
	assert(n > 0);

	if (n == 1)
	{
		printf("%d -> %d\n", from, to);
		return;
	}

	solve_hanoi_recursive(n - 1, from, to, temp);
	
	printf("%d -> %d\n", from, to);

	solve_hanoi_recursive(n - 1, temp, from, to);
}

uint32_t get_binomial_coefficient_recursive(const uint32_t n, const uint32_t k)
{
	assert(n > 0);

	if (k == 0 || n == k)
	{
		return 1;
	}

	return get_binomial_coefficient_recursive(n - 1, k - 1) + get_binomial_coefficient_recursive(n - 1, k);
}

uint32_t get_binomial_coefficient(const uint32_t n, const uint32_t k)
{
	assert(n > 0);

	if (k == 0)
	{
		return 1;
	}

	return get_factorial(n) / (get_factorial(n - k) * get_factorial(k));
}

