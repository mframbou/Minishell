/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:18:16 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 16:28:19 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char *argv[])
{
	int	print_nl;
	int	i;

	i = 1;
	print_nl = 1;
	if (argc >= 2 && ft_strcmp(argv[i], "-n") == 0)
	{
		i++;
		print_nl = 0;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
		if (i != argc)
			printf(" ");
	}
	if (print_nl)
		printf("\n");
}
