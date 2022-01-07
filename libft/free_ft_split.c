/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:13 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 17:32:33 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	free_ft_split(char **ft_split_return)
{
	int	i;

	i = 0;
	if (!ft_split_return)
		return ;
	while (ft_split_return[i])
		free(ft_split_return[i++]);
	free(ft_split_return);
}
