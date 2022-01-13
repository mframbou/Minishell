/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 13-01-2022 13:27 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 =-=-=-=-= V1 FUNCTION (Better readability) =-=-=-=-=-=

char	*get_line_till_space_or_quote(char *str) 
{
	int	i;
	int	j;
	int	closed_quote_found;

	i = 0;
	closed_quote_found = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i] == '"' || str[i] == '\'')
	{
		if (is_closed_quote(&(str[i])))
			return (ft_substr(str, 0, i));
		else
		{
			i++;
			while (str[i] && !ft_isspace(str[i]) && \
			str[i] != '"' && str[i] != '\'')
				i++;
			if (str[i] == '"' || str[i] == '\'')
			{
				if (is_closed_quote(&(str[i])))
					return (ft_substr(str, 0, i));
				else
				{
					while (str[i] && !ft_isspace(str[i]))
						i++;
					return (ft_substr(str, 0, i));
				}
			}
			else
				return (ft_substr(str, 0, i));
		}
	}
	return (ft_substr(str, 0, i));
}
*/

/*
	If we found a non-closing quote, then count it as part of the argument
*/
static char	*get_line_till_space_or_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i] == '"' || str[i] == '\'')
	{
		if (!is_closed_quote(&(str[i])))
		{
			i++;
			while (str[i] && !ft_isspace(str[i]) && str[i] != '"' \
			&& str[i] != '\'')
				i++;
			if ((str[i] == '"' || str[i] == '\'') \
			&& !is_closed_quote(&(str[i])))
				while (str[i] && !ft_isspace(str[i]))
					i++;
		}
	}
	return (ft_substr(str, 0, i));
}

static char	*get_line_till_any_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (ft_substr(str, 0, i + 1));
}

/*
	test"i' ca' marche ou pas ?

	special case => ['test"i', 'ca', 'marche', 'ou', 'pas']
*/
static char	*get_line_till_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

/*
	Retrieve the argument, only special case is if the arg == '' or ""
	In which case we just do i += 2 to skip the quotes 
		and return NULL since it's like an empty arg
*/
char	*get_one_arg(char *str, int *i)
{
	char	*res;
	int		closed_quote_distance;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		closed_quote_distance = is_closed_quote(&(str[*i]));
		if (closed_quote_distance == 0)
			res = get_line_till_space(&(str[*i]));
		else if (closed_quote_distance == 1)
		{
			*i += 2;
			return (NULL);
		}
		else
			res = get_line_till_any_quote(&(str[*i]));
	}
	else
		res = get_line_till_space_or_quote(&str[*i]);
	return (res);
}
