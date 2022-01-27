/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 27-01-2022 12:49 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
		i++;
	else
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	if (i > 10)
		return (0);
	return (1);
}

static void	set_numeric_arg_error(char *arg, int output_fd)
{
	ft_putstr_fd("exit: ", output_fd);
	ft_putstr_fd(arg, output_fd);
	ft_putstr_fd(": numeric argument required\n", output_fd);
	set_exit_status(255);
	set_should_exit(1);
}

void	exit_command(char **argv, int output_fd)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		set_should_exit(1);
	else if (argc == 2)
	{
		if (is_digit_str(argv[1]))
		{
			set_should_exit(1);
			set_exit_status(ft_atoi(argv[1]));
		}
		else
		{
			set_numeric_arg_error(argv[1], output_fd);
		}
	}
	else
	{
		ft_putstr_fd("exit: too many arguments\n", output_fd);
		set_exit_status(EXIT_FAILURE);
	}
}
