/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:57:52 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/18 13:43:10 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void	cd(int argc, char *argv[])
{
	if (argc == 0 && chdir(getenv("HOME")) == -1)
		perror(errno);
	else if (chdir(argv[0]) == -1)
		perror(errno);
}
