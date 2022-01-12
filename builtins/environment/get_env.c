/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created:   by                 `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated:   by                     /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

static char	*generate_var_string(t_env_link *var)
{
	char	*res;
	int		str_len;

	str_len = ft_strlen(var->var.key) + 1 + ft_strlen(var->var.value) + 1;
	res = (char *) malloc(sizeof(char) * str_len);
	if (res)
	{
		ft_bzero(res, sizeof(char) * str_len);
		ft_strlcat(res, var->var.key, str_len);
		ft_strlcat(res, "=", str_len);
		ft_strlcat(res, var->var.value, str_len);
	}
	return (res);
}

/*
	We can use this because res[i] was set to NULL, marking the end
	of our array (since it's always the last one that fails, because if
	it does it returns)
*/
static void	*free_all_return_null(char **str_array)
{
	free_ft_split(str_array);
	return (NULL);
}

static int	count_lst_size(t_env_link *start)
{
	int	i;

	i = 0;
	while (start)
	{
		i++;
		start = start->next;
	}
	return (i);
}

/*
	Strlen KEY = '='  + Strlen VALUE + '\0'
*/
char	**get_env_as_string_array(void)
{
	t_env_link	*curr;
	char		**res;
	int			i;

	i = 0;
	curr = *get_var_list();
	res = (char **) malloc(sizeof(char *) * (count_lst_size(curr) + 1));
	if (res)
	{
		i = 0;
		curr = *get_var_list();
		while (curr)
		{
			res[i] = generate_var_string(curr);
			if (!res[i])
				return (free_all_return_null(res));
			i++;
			curr = curr->next;
		}
		res[i] = NULL;
	}
	return (res);
}
