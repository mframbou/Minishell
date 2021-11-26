/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:30:21 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 18:05:52 by mframbou         ###   ########.fr       */
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
	char	*key;
	char	*value;

	add_env_variable(key, value);
}
