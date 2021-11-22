/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:53:17 by oronda            #+#    #+#             */
/*   Updated: 2021/11/22 16:36:21 by oronda           ###   ########.fr       */
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
		char *test[3] = {"HOME=/Users/oronda", "crakito", NULL};
		int i = execve("./cd", args, test);
		printf("%d \n", i);
	}
}
