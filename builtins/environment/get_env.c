/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:48:20 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/26 19:44:58 by oronda           ###   ########.fr       */
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
	res = malloc(sizeof(char *) * (i + 1));
	if (res)
	{
		i = 0;
		curr = *get_var_list();
		while (curr)
		{
			res[i++] = curr->var.value;
			curr = curr->next;
		}
		res[i] = NULL;
	}
}
