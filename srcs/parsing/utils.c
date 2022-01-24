/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:36 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_in_filename(char c)
{
	return (!(c == '>' || c == '<' || c == '|' || c == ':' || c == '&'));
}

/*
	Simply removes one char from string, takes string pointer and index
	("test", 1) => "tst"
*/
void	remove_char_from_string(char **str, int index)
{
	char	*res;
	int		new_len;
	char	old_char;

	if (index > ft_strlen(*str) - 1 || index < 0)
		return ;
	new_len = ft_strlen(*str) - 1;
	res = ft_malloc(sizeof(char) * (new_len + 1));
	if (res)
	{
		ft_bzero(res, new_len + 1);
		old_char = (*str)[index];
		(*str)[index] = '\0';
		ft_strlcat(res, *str, new_len + 1);
		(*str)[index] = old_char;
		ft_strlcat(res, &((*str)[index + 1]), new_len + 1);
		//free(*str);
		*str = res;
	}
}

/*
	As remove_char_from_string but for a whole substring (between start and end)
*/
void	remove_substr_from_string(char **str, int start, int end)
{
	while (--end >= start)
		remove_char_from_string(str, start);
}

int	is_closed_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
		return (0);
	return (i);
}



/*
nt		i;
	int		stack_top;

	ft_bzero(parenthesis_stack, 4096);
	i = 0;
	stack_top = 0; // stack_top 1 = 1 ( in our stack, so when accessing use index - 1
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"') // skip quotes
			i += is_closed_quote(&(line[i]));
		if (line[i] == '(')
		{
			parenthesis_stack[stack_top++] = '(';
		}
		else if (line[i] == ')')
		{
			if (stack_top == 0)
			{
				printf("Syntax error near index %d ('%c'): too many closing parentheses\n", i, line[i]);
				return (1);
			}
			if (parenthesis_stack[stack_top - 1] == '(')
				parenthesis_stack[stack_top--] = 0;
		}
		i++;
	}
	if (stack_top != 0)
	{
		printf("Syntax error: too many opening parentheses\n");
		return (1);
	}
*/

/*
	We cannot use the first closing parenthesis we find, if we have
	(echo test (salut) pouet)
			we need to match 1st with last
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
	i++; // Skip the first '('
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += is_closed_quote(&(str[i]));
		else if (str[i] == '(')
			parentheses_stack[stack_top++] = '(';
		else if (str[i] == ')') // No need to check if the stack is empty since we already checked it previously
		{
			if (parentheses_stack[stack_top - 1] == '(')
				parentheses_stack[stack_top--] = 0;
			if (stack_top == 0) // If it is the matching parenthesis
				return (i);
		}
		i++;
	}
	return (0); // We should never reach this point
}



/*
	Inserts str into src at index index.

	"Test chad", "giga ", 5 => "Test giga chad"

	i = res index
	j = src index
*/
char	*insert_str_in_str(char *src, char *str, int index)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	res = ft_malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(str) + 1));
	if (index < 0 || index > ft_strlen(src))
		return (NULL);
	if (res)
	{
		i = 0;
		j = 0;
		k = 0;
		while (src[j] && j < index)
			res[i++] = src[j++];
		while (str[k])
			res[i++] = str[k++];
		while (src[j])
			res[i++] = src[j++];
		res[i] = '\0';
	}
	//free(src);
	//free(str);
	return (res);
}
