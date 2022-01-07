/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:54:20 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 18:03:41 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_cmd(char *argv[])
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
		perror(argv[1]);
}
