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

void	env_command(char **argv, int output_fd)
{
	t_env_link	**var_list;
	t_env_link	*curr;
	int			i;

	(void) argv;
	var_list = get_var_list();
	curr = *var_list;
	while (curr)
	{
		if (curr->var.value[0])
		{
			ft_putstr_fd(curr->var.key, output_fd);
			ft_putchar_fd('=', output_fd);
			ft_putstr_fd(curr->var.value, output_fd);
			ft_putchar_fd('\n', output_fd);
		}
		curr = curr->next;
	}
}
