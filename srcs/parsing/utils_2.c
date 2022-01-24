/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 18-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:31 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	DOES NOT FREE

	i = str array index
	j = result index
	k = current str in array index

	Add a space after each string (except for last, so remove 1 at the end)
	Which "counters" the + 1 for the '\0'
*/
char	*convert_str_array_to_one_line(char **array)
{
	int		total_len;
	int		i;
	int		j;
	int		k;
	char	*res;

	total_len = 0;
	i = 0;
	while (array[i])
		total_len += ft_strlen(array[i++]) + 1;
	res = ft_malloc(sizeof(char) * (total_len));
	if (res)
	{
		i = 0;
		j = 0;
		while (array[i])
		{
			k = 0;
			while (array[i][k])
				res[j++] = array[i][k++];
			if (array[i + 1])
				res[j++] = ' ';
			i++;
		}
		res[j] = 0;
	}
	return (res);
}
