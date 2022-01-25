/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 17:21 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
		ft_free(*str);
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
	ft_free(src);
	ft_free(str);
	return (res);
}
