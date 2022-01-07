/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:34:12 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 18:00:41 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
	If the string passed is null, getcwd allocates it with a buffer of size n,
	If n is 0, getcwd automatically malloc the required length
	Returns the address of the buffer (which changed because it was malloc'ed)
*/
void	pwd_cmd(void)
{
	char	*curr_path;

	curr_path = NULL;
	curr_path = getcwd(curr_path, 0);
	printf("%s\n", curr_path);
	free(curr_path);
}
