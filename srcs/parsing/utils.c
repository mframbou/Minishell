/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 17-01-2022 13:04 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
	res = malloc(sizeof(char) * (new_len + 1));
	if (res)
	{
		ft_bzero(res, new_len + 1);
		old_char = (*str)[index];
		(*str)[index] = '\0';
		ft_strlcat(res, *str, new_len + 1);
		(*str)[index] = old_char;
		ft_strlcat(res, &((*str)[index + 1]), new_len + 1);
		free(*str);
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
