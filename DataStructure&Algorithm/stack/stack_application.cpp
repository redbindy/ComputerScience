#include "stack_application.h"

using namespace stack;

bool stack_application::is_valid_parentheses(const char* p_str, const size_t len)
{
	assert(p_str != nullptr);

	const char* p_input_str = p_str;

	stack_t<char> stack = create<char>(len);
	{
		push(&stack, *p_input_str);
		for (++p_input_str; *p_input_str != '\0'; ++p_input_str) {

			const char curr_ch = *p_input_str;

			switch (curr_ch) {
			case '(':
			case '{':
			case '[':
				push(&stack, curr_ch);
				break;

			case ')':
				if (peek(&stack) != '(') {
					goto BREAK_LOOP;
				}
				else {
					pop(&stack);
				}
				break;

			case '}':
				if (peek(&stack) != '{') {
					goto BREAK_LOOP;
				}
				else {
					pop(&stack);
				}
				break;

			case ']':
				if (peek(&stack) != '[') {
					goto BREAK_LOOP;
				}
				else {
					pop(&stack);
				}
				break;

			default:
				continue;
			}
		}
	BREAK_LOOP:;
	}
	bool is_valid = is_empty(&stack);
	delete_stack(&stack);

	return is_valid;
}

static const char* skip_whitespace(const char* p_str)
{
	const char* p = p_str;
	while (isspace(*p)) {
		++p;
	}

	return p;
}

enum {
	DEFAULT_CAPACITY = 100
};

double stack_application::calculate_postfix_expression(const char* p_expression)
{
	assert(p_expression != nullptr);
	// 올바른 형식만 입력으로 들어온다고 가정

	stack_t<double> values = create<double>(DEFAULT_CAPACITY);
	{
		const char* p_expr = skip_whitespace(p_expression);
		while (*p_expr != '\0') {
			const char curr_ch = *p_expr;

			if (curr_ch >= '0' && curr_ch <= '9' || curr_ch == '.') {
				double value;
				sscanf(p_expr, "%lf", &value);

				push(&values, value);
			}
			else {
				switch (curr_ch) {
				case '+':
					{
						double rhs = pop(&values);
						double lhs = pop(&values);

						push(&values, lhs + rhs);
					}
					break;

				case '-':
					{
						double rhs = pop(&values);
						double lhs = pop(&values);

						push(&values, lhs - rhs);
					}
					break;

				case '*':
					{
						double rhs = pop(&values);
						double lhs = pop(&values);

						push(&values, lhs * rhs);
					}
					break;

				case '/':
					{
						double rhs = pop(&values);
						double lhs = pop(&values);

						push(&values, lhs / rhs);
					}
					break;

				default:
					assert(false);
					break;
				}
			}

			p_expr = skip_whitespace(p_expr + 1);
		}
	}
	double result = pop(&values);

	delete_stack(&values);

	return result;
}

void stack_application::convert_infix_to_postfix(const char* p_expression, char* p_out_result)
{
	assert(p_expression != nullptr);
	assert(p_out_result != nullptr);

	stack_t<char> operators = create<char>(DEFAULT_CAPACITY);
	{
		const char* p_expr = p_expression;
		char buffer[DEFAULT_CAPACITY];

		while (*p_expr != '\0') {
			const char curr_ch = *p_expr;

			if (curr_ch >= '0' && curr_ch <= '9' || curr_ch == '.') {
				double value;
				sscanf(p_expr, "%lf", &value);

				sprintf(buffer, " %.lf", value);
				strcat(p_out_result, buffer);
			}
			else {
				switch (curr_ch) {
				case '+':
				case '-':
					while (!is_empty(&operators)) {

						const char op = peek(&operators);
						switch (op)
						{
						case '+':
						case '-':
						case '*':
						case '/':
							pop(&operators);

							sprintf(buffer, " %c", op);
							strcat(p_out_result, buffer);

							break;

						default:
							goto BREAK_LOOP;
						}
					}
				BREAK_LOOP:
					push(&operators, curr_ch);

					break;

				case '*':
				case '/':
					while (!is_empty(&operators)) {
						const char op = peek(&operators);
						if (op == '+' || op == '-') {
							break;
						}

						pop(&operators);

						sprintf(buffer, " %c", op);
						strcat(p_out_result, buffer);
					}

					push(&operators, curr_ch);

					break;

				case '(':
					push(&operators, curr_ch);
					break;

				case ')':
					while (!is_empty(&operators)) {
						const char op = pop(&operators);
						if (op == '(') {
							break;
						}

						sprintf(buffer, " %c", op);
						strcat(p_out_result, buffer);
					}
					break;

				default:
					assert(false);
					break;
				}
			}

			p_expr = skip_whitespace(p_expr + 1);
		}

		while (!is_empty(&operators)) {
			const char op = pop(&operators);
			sprintf(buffer, " %c", op);

			strcat(p_out_result, buffer);
		}
	}
	delete_stack(&operators);
}

bool stack_application::can_exit_maze(
	char* p_maze,
	const int width, const int height,
	const point_t entry_point,
	const point_t exit_point
)
{
	bool can_exit = false;

	stack_t<point_t> coords = create<point_t>(width * height);
	{
		push(&coords, entry_point);

		while (!is_empty(&coords)) {
			point_t curr_point = peek(&coords);

			if (curr_point.x == exit_point.x && curr_point.y == exit_point.y) {
				can_exit = true;

				break;
			}

			if (curr_point.x < 0 || curr_point.x >= width
				|| curr_point.y < 0 || curr_point.y >= height
				|| p_maze[curr_point.y * width + curr_point.x] != ' ') {

				pop(&coords);

				continue;
			}

			p_maze[curr_point.y * width + curr_point.x] = 'x';

			point_t right = { curr_point.x + 1, curr_point.y };
			point_t down = { curr_point.x, curr_point.y + 1 };
			point_t left = { curr_point.x - 1, curr_point.y };
			point_t up = { curr_point.x, curr_point.y - 1 };

			push(&coords, up);
			push(&coords, left);
			push(&coords, down);
			push(&coords, right);
		}
	}
	delete_stack(&coords);

	return can_exit;
}
