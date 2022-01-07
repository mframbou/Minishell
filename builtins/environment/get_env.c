/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:48:20 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 16:55:52 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

/*
	Strlen KEY = '='  + Strlen VALUE + '\0'
*/
char	**get_env_as_string_array(void)
{
	t_env_link	*curr;
	char		**res;
	int			i;
	int			str_len;

	i = 0;
	curr = *get_var_list();
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	res = (char **) malloc(sizeof(char *) * (i + 1));
	if (res)
	{
		i = 0;
		curr = *get_var_list();
		while (curr)
		{
			str_len = ft_strlen(curr->var.key) + 1 + \
						ft_strlen(curr->var.value) + 1;
			res[i] = (char *) malloc(sizeof(char) * str_len);
			ft_bzero(res[i], sizeof(char) * str_len);
			ft_strlcat(res[i], curr->var.key, str_len);
			ft_strlcat(res[i], "=", str_len);
			ft_strlcat(res[i], curr->var.value, str_len);
			i++;
			curr = curr->next;
		}
		res[i] = NULL;
	}
	return (res);
}
