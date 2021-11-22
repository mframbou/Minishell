/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:46:32 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/18 17:38:19 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	unset(int argc, char *argv[])
{
	/*
		Check arg validity
		If not a single string, split on ':'
		Set key / values
	*/
	while (argc)
		remove_env_variable(argv[--argc]);
}
