/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 19-01-2022 14:27 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

void	env_command(char **argv, int output_fd)
{
	t_env_link	**var_list;
	t_env_link	*curr;

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
	set_exit_status(EXIT_SUCCESS);
}
