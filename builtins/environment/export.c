/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:30:21 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 15:53:20 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
	Check arg validity
	If not a single string, split on ':'
	Set key / values
*/
int	main(int argc, char *argv[])
{
	char	*key;
	char	**values;

	add_env_variable(key, values);
}
