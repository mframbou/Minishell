/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:46:32 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 17:46:05 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
	Check arg validity
	If not a single string, split on ':'
	Set key / value
*/
void	unset_command(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
		remove_env_variable(argv[i++]);
}
