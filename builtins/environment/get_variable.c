/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:21:18 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 18:06:06 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

char	*get_env_variable(char *key)
{
	t_env_link	*var_lst;

	var_lst = *(get_var_list());
	while (var_lst)
	{
		if (ft_strcmp(var_lst->var.key, key) == 0)
			return (var_lst->var.value);
		var_lst = var_lst->next;
	}
	return (NULL);
}
