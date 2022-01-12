/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:30:21 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 17:42:16 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
	Check arg validity
	If not a single string, split on '='
	Set key / value
*/
void	export_command(char *argv[], int output_fd)
{
	char	**values;
	int		i;

	i = 1;
	while (argv[i])
	{
		values = ft_split(argv[i], '=');
		if (!values || !values[0])
		{
			free_ft_split(values);
			ft_putstr_fd("Invalid syntax\n", output_fd);
		}
		if (values[1])
			add_env_variable(ft_strdup(values[0]), ft_strdup(values[1]));
		else
			add_env_variable(ft_strdup(values[0]), ft_strdup(""));
		free_ft_split(values);
		i++;
	}
}
