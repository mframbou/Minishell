/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:40:17 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 17:37:19 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

void	env_command(void)
{
	t_env_link	**var_list;
	t_env_link	*curr;
	int			i;

	var_list = get_var_list();
	curr = *var_list;
	while (curr)
	{
		if (curr->var.value[0])
			printf("%s=%s\n", curr->var.key, curr->var.value);
		curr = curr->next;
	}
}
