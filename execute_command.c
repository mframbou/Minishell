/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:20:59 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/10 17:33:46 by mframbou         ###   ########.fr       */
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
		/*int pipe_fd2[2];
		
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
		}*/
		while (read(pipe_fd[0], &buf, 1) > 0)
			write(pipe_fd[1], &buf, 1);
		close(pipe_fd[0]);
		//dup2(STDOUT_FILENO, /*fd*/ pipe_fd[0]);
		// Do things
		close(pipe_fd[0]);
	}
}






static int	perror_return(char *str)
{
	perror(str);
	return (-2);
}

static int	exec_and_redirect_stdout(int pipe_fd[2], char *program_path, \
									char **args)
{
	char	**env;

	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(pipe_fd[1]);
		return (perror_return("dup2 failure"));
	}
	env = get_env_as_string_array();
	free_ft_split(env);
	close(pipe_fd[1]);
	execve(program_path, args, env);
	return (perror_return("execve failure"));
}

/*
	pipe_fd[0] = read end
	pipe_fd[1] = write end

	Capture program stdout and redirect it into the pipe.
	Returns the end to read from for next command.
	Stays opened so caller MUST CLOSE FD

	If we reach the return in the child process, it means execve has failed

	When closing a FD, the pipe itself still exists, only the associated
	descriptors are deleted from what I understood
*/
int	execute_program_from_args(char *program_path, char **args)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror_return("pipe failure"));
	else
	{
		if (fork() == 0)
		{
			exec_and_redirect_stdout(pipe_fd, program_path, args);
			return (-2);
		}
		else
			close(pipe_fd[1]);
	}
	return (pipe_fd[0]);
}

/*
	If input fd = -1, we only use args as input
*/
int	execute_program(int input_fd, char *program_path, char **args)
{
	int	output_read_fd;

	output_read_fd = -1;
	if (input_fd == -1)
	{
		output_read_fd = execute_program_from_args(program_path, args);
		if (output_read_fd == -2)
			return (-1);
	}
	else
	{
		
	}
	return (output_read_fd);
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