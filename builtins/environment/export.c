/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:30:21 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/18 16:48:25 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	export(int argc, char *argv[])
{
	char	*key;
	char	**values;
	/*
		Check arg validity
		If not a single string, split on ':'
		Set key / values
	*/
	add_env_variable(key, values);
}
