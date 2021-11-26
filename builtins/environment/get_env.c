/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:48:20 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 18:17:01 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

char	**get_env_as_string_array(void)
{
	t_env_link	*curr;
	char		**res;
	int			i;
	
	i = 0;
	curr = *get_var_list();
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	res = malloc(sizeof(char *) * i);
	if (res)
	{
		i = 0;
		curr = *get_var_list();
		while (curr)
		{
			res[i++] = curr->var;
			curr = curr->next;
		}
	}
}
