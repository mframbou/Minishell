/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:40:17 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/18 16:47:48 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

void	env(int argc, char *argv[])
{
	t_env_link	**var_list;
	t_env_link	*curr;
	int			i;

	var_list = get_var_list();
	curr = *var_list;
	while (curr)
	{
		printf("%s=", curr->var.key);
		i = 0;
		while (curr->var.values[i])
		{
			printf("%s", curr->var.values[i]);
			if (curr->var.values[i + 1])
				printf(":");
			i++;
		}
		printf("\n");
		curr = curr->next;
	}
}
