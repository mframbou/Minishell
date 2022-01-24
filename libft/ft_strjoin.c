/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:44:03 by mframbou          #+#    #+#             */
/*   Updated: 24-01-2022 01:35 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_malloc/ft_malloc.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		i++;
		j++;
	}
	res = (char *) ft_malloc(sizeof(char) * (i + 1));
	if (res)
	{
		res[i] = 0;
		while (j-- > 0)
			res[--i] = s2[j];
		while (i-- > 0)
			res[i] = s1[i];
	}
	return (res);
}
