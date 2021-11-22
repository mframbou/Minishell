/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:57:52 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 16:12:05 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char *argv[])
{
	int	res;

	if (argc == 1)
		res = chdir(getenv("HOME"));
	else
		res = chdir(argv[1]);
	if (res == -1)
		perror(argv[1]);
}
