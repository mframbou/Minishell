/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 24-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 19:43 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
