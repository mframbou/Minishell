/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:53:17 by oronda            #+#    #+#             */
/*   Updated: 2021/11/22 17:41:35 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../builtins/builtins.h"
#include <unistd.h>

void	parse(char *str)
{
	char **args;
	
	
	args = ft_split(str,' ');
	
	if (!ft_strcmp(args[0], "cd"))
	{
		char *test[2];
		test[0] = getenv("HOME");
		test[1] = 0;
		if (fork() == 0)
			execve("./cd", args, test);
	}
}
