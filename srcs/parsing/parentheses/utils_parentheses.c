/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 24-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 17:33 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	second = parenthesis index - 1 since we removed the first one
*/
char	*remove_outer_parentheses(char *str)
{
	int		i;
	int		first;
	int		second;
	char	*res;

	i = 0;
	res = ft_strdup(str);
	while (res[i])
	{
		if (res[i] == '(' && is_closed_parenthesis(&res[i]))
		{
			first = i;
			second = is_closed_parenthesis(&(res[i])) - 1;
			remove_char_from_string(&res, first);
			remove_char_from_string(&res, second);
			break ;
		}
		i++;
	}
	return (res);
}

int	has_parentheses_to_interpret(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += is_closed_quote(&(str[i]));
		else if (str[i] == '(' && is_closed_parenthesis(&str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
	We cannot use the first closing parenthesis we find, if we have
	(echo test (salut) pouet)
			we need to match 1st with last

	- skip the first '(' (that's why i = 0 and ++i it makes i start at 1)
	- if we find another '(' add it on the stack
	- else if we find ')' remove one '(' from the char
	return when we find a ')' which makes the stack empty, which means it
		matches with the first '('
*/
int	is_closed_parenthesis(char *str)
{
	int		i;
	char	parentheses_stack[4096];
	int		stack_top;

	if (str[0] != '(')
		return (0);
	stack_top = 0;
	ft_bzero(parentheses_stack, 4096);
	i = 0;
	parentheses_stack[stack_top++] = '(';
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += is_closed_quote(&(str[i]));
		else if (str[i] == '(')
			parentheses_stack[stack_top++] = '(';
		else if (str[i] == ')')
		{
			if (parentheses_stack[stack_top - 1] == '(')
				parentheses_stack[stack_top--] = 0;
			if (stack_top == 0)
				return (i);
		}
	}
	return (0);
}

/*
	Uses a stack of 4096 because it's the max line length in bash

	Return 0 = valid
	1 = invalid
	automatically prints the error

	When we add first '(', stack top = 1, but since it's an array we need
	to access 0, so always access stack_top-1 if stack_top > 0

	return printf to gain lines (since printf return the number it's != 0)
*/
int	are_parentheses_invalid(char *line)
{
	char	parenthesis_stack[4096];
	int		i;
	int		stack_top;

	ft_bzero(parenthesis_stack, 4096);
	i = -1;
	stack_top = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i += is_closed_quote(&(line[i]));
		if (line[i] == '(')
			parenthesis_stack[stack_top++] = '(';
		else if (line[i] == ')')
		{
			if (stack_top == 0)
				return (printf("Syntax error near index %d ('%c'): \
								too many closing parentheses\n", i, line[i]));
			if (parenthesis_stack[stack_top - 1] == '(')
				parenthesis_stack[stack_top--] = 0;
		}
	}
	if (stack_top != 0)
		return (printf("Syntax error: too many opening parentheses\n"));
	return (0);
}
