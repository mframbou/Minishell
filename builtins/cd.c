/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:54:20 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/10 11:28:16 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_command(char *argv[], int output_fd)
{
	int		res;
	char	*home_path;

	res = 0;
	if (argv[1] == NULL)
	{
		home_path = getenv("HOME");
		if (home_path)
			res = chdir(home_path);
	}
	else
		res = chdir(argv[1]);
	if (res == -1)
	{
		ft_putstr_fd(MINISHELL_PROMPT, output_fd);
		ft_putstr_fd("cd: ", output_fd);
		ft_putstr_fd(argv[1], output_fd);
		ft_putstr_fd(strerror(errno), output_fd);
	}
}
