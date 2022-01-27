/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:48:13 by mframbou          #+#    #+#             */
/*   Updated: 24-01-2022 19:54 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc/ft_malloc.h"
#include <stdlib.h>

void	free_ft_split(char **ft_split_return)
{
	int	i;

	i = 0;
	if (!ft_split_return)
		return ;
	while (ft_split_return[i])
		ft_free(ft_split_return[i++]);
	ft_free(ft_split_return);
}
