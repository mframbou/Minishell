/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:20:59 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 18:00:10 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EXECS_PATH "./execs/"
/*
	Get only the parsed string list as argument (eg: "echo" "Salut bg", "ca", "va?") 
*/

static int	is_builtin(char *program)
{
	if (ft_strcmp(program, "echo") == 0)
		return (1);
	else if (ft_strcmp(program, "cd") == 0)
		return (1);
	else if (ft_strcmp(program, "pwd") == 0)
		return (1);
	else if (ft_strcmp(program, "export") == 0)
		return (1);
	else if (ft_strcmp(program, "unset") == 0)
		return (1);
	else if (ft_strcmp(program, "env") == 0)
		return (1);
	else if (ft_strcmp(program, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(char *builtin, char **args)
{
	char	*program_path;
	int		program_path_length;

	program_path_length = (ft_strlen(EXECS_PATH) + ft_strlen(builtin) + 1);
	program_path = malloc(sizeof(char) * program_path_length);
	ft_bzero(program_path, program_path_length);
	ft_strlcat(program_path, EXECS_PATH, program_path_length);
	ft_strlcat(program_path, builtin, program_path_length);
	// We give it even the program name by convention
	if (fork() == 0)
		execve(program_path, args, NULL);
	free(program_path);
}

int	execute_command(char **args)
{
	char	*program;

	program = args[0];
	if (program && is_builtin(program))
		execute_builtin(program, args);
	else
	{
		
	}
}
