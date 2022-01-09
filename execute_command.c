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
}*/
/*
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
*/








void	execute_builtin(char **args)
{
	if (strcmp(args[0], "echo") == 0)
		execute_program("./execs/echo", args);
	else if (strcmp(args[0], "export") == 0)
		export_command(args);
	else if (strcmp(args[0], "unset") == 0)
		unset_command(args);
	else if (strcmp(args[0], "env") == 0)
		env_command();
	else if (strcmp(args[0], "cd") == 0)
		cd_cmd(args);
	else if (strcmp(args[0], "pwd") == 0)
		pwd_cmd();
	else if (strcmp(args[0], "exit") == 0)
	{
		printf("Clean exit TODO\n");
		exit(EXIT_SUCCESS);
	}
}

void	execute_program(char *program_path, char **args)
{
	int		return_val;

	if (fork() == 0)
	{
		execve(program_path, args, get_env_as_string_array());
		printf("Just executed %s\n", args[0]);
	}
	else
	{
		waitpid(-1, &return_val, 0);
		printf("Returned value: %d\n", return_val);
	}
}

