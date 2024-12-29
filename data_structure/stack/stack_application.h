#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cassert>
#include <cctype>

#include "stack.h"

namespace stack_application
{
	bool is_valid_parentheses(const char* const p_str, const size_t len);

	double calculate_postfix_expression(const char* const p_expression);
	void convert_infix_to_postfix(const char* const p_expression, char* const p_out_result);

	typedef struct {
		int x;
		int y;
	} point_t;

	bool can_exit_maze(
		char* p_maze,
		const int width, const int height,
		const point_t entry_point,
		const point_t exit_point
	);
}