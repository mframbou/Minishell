/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:20:59 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/10 15:51:08 by mframbou         ###   ########.fr       */
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
		execute_program(0, "./execs/echo", args);
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

/*
	pipe[0] = read
	pipe[1] = write

	dup2 makes arg2 "redirect" to arg1
	so dup2(FD, STDOUT) redirects STDOUT to FD

	Returns the pipe read fd for next pipe
*/
#include <fcntl.h>
int	execute_program(int input_fd, char *program_path, char **args)
{
	int		pipe_success;
	int		pipe_fd[2];
	char	**env;

	pipe_success = 0;
	pipe_success = pipe(pipe_fd);
	if (fork() == 0)
	{
		// Capture STDOUT and redirect to pipe output (so write to pipe input)
		close(pipe_fd[0]); // We only write so close READ end
		
		dup2(pipe_fd[1], STDOUT_FILENO);
		env = get_env_as_string_array();
		execve(program_path, args, env);
		free_ft_split(env);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]); // We only read so close WRITE end
		//printf("Pipe redirecting ...\n");
		char buf;

		// test redirecting to another pipe to simulate piping
		int pipe_fd2[2];
		
		pipe(pipe_fd2);
		if (fork() == 0)
		{
			close(pipe_fd2[1]);

			while (read(pipe_fd2[0], &buf, 1) > 0)
			{
				write(STDOUT_FILENO, &buf, 1);
			}
			close(pipe_fd2[0]);
		}
		else
		{
			close (pipe_fd2[0]);
			while (read(pipe_fd[0], &buf, 1) > 0)
				write(pipe_fd2[1], &buf, 1);
			close(pipe_fd2[1]);
		}
		//dup2(STDOUT_FILENO, /*fd*/ pipe_fd[0]);
		// Do things
		close(pipe_fd[0]);
	}
}

/*
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
		printf("Returned value: %d\n", WEXITSTATUS(return_val));
	}
}
*/