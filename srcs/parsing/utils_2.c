/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 18-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 17:22 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	DOES NOT FREE

	i = str array index
	j = result index
	k = - result length in first part and 
		- current str in array index in second part

	Add a space after each string (except for last, so remove 1 at the end)
	Which "counters" the + 1 for the '\0'
*/
char	*convert_str_array_to_one_line(char **array)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	k = 0;
	i = 0;
	while (array[i])
		k += ft_strlen(array[i++]) + 1;
	res = ft_malloc(sizeof(char) * (k));
	if (res)
	{
		i = -1;
		j = 0;
		while (array[++i])
		{
			k = 0;
			while (array[i][k])
				res[j++] = array[i][k++];
			if (array[i + 1])
				res[j++] = ' ';
		}
		res[j] = '\0';
	}
	return (res);
}

/*
	Compares first string with every other, second with every other (except 1st)
	and so on, always swap if the 1st is bigger than 2nd
*/
void	sort_string_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '/')
			return (1);
	return (0);
}
