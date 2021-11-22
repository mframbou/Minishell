/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:57:52 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 16:38:24 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char *argv[])
{
	int		res;
	char	*home_path;

	if (argc == 1)
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
