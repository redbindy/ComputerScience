#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cassert>
#include <cctype>

#include "stack.h"

bool is_valid_parentheses(const char* p_str, const size_t len);

double calculate_postfix_expression(const char* p_expression);
void convert_infix_to_postfix(const char* p_expression, char* p_out_result);

typedef struct point {
	int x;
	int y;
} point_t;

bool can_exit_maze(
	char* p_maze, 
	const int width, const int height, 
	const point_t entry_point, 
	const point_t exit_point
);