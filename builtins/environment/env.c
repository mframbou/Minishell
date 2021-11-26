/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:40:17 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 18:04:55 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

int	main(int argc, char *argv[])
{
	t_env_link	**var_list;
	t_env_link	*curr;
	int			i;

	var_list = get_var_list();
	curr = *var_list;
	while (curr)
	{
		printf("%s=%s\n", curr->var.key, curr->var.value);
		curr = curr->next;
	}
}
