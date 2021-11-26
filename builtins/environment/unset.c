/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:46:32 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 18:06:28 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
	Check arg validity
	If not a single string, split on ':'
	Set key / value
*/
int	main(int argc, char *argv[])
{
	while (argc)
		remove_env_variable(argv[--argc]);
}
