/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:25:46 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/18 15:10:03 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void)
{
	static t_env_link	*var_list = NULL;

	return (&var_list);
}

void	free_var_list(void)
{
	free(*(get_var_list()));
}
