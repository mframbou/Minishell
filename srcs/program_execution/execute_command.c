/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 27-01-2022 14:26 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	pipe[0] = read
	pipe[1] = write

	dup2 makes arg2 "redirect" to arg1
	so dup2(FD, STDOUT) redirects STDOUT to FD

	Returns the pipe read fd for next pipe
*/

static int	exec_and_redirect_stdout(int pipe_fd[2], char *program_path, \
									char **args)
{
	char	**env;

	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		write(1, "Error occured\n", 8);
		close(pipe_fd[1]);
		return (perror_return("dup2 stdout failure"));
	}
	env = get_env_as_string_array();
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
	int		pid;

	if (pipe(pipe_fd) == -1)
		return (perror_return("pipe failure"));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			exec_and_redirect_stdout(pipe_fd, program_path, args);
			return (-2);
		}
		else
		{
			close(pipe_fd[1]);
			g_pid = pid;
		}
	}
	return (pipe_fd[0]);
}

static int	execute_program_from_args_and_fd(int read_fd, char *program_path, \
											char **args)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) == -1)
		return (perror_return("pipe failure"));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(read_fd, STDIN_FILENO);
			close(read_fd);
			exec_and_redirect_stdout(pipe_fd, program_path, args);
			return (-2);
		}
		else
		{
			g_pid = pid;
			close(read_fd);
			close(pipe_fd[1]);
		}
	}
	return (pipe_fd[0]);
}

/*
	If input fd = -1, we only use args as input

	if output_read_fd = -2 the error is already printed so just return
*/
int	execute_program(int input_fd, char *program_path, char **args)
{
	int	output_read_fd;

	output_read_fd = -1;
	if (input_fd == -1)
	{
		output_read_fd = execute_program_from_args(program_path, args);
		if (output_read_fd == -2)
			return (-2);
	}
	else
	{
		output_read_fd = execute_program_from_args_and_fd(input_fd, \
														program_path, args);
	}
	return (output_read_fd);
}

/*
	Read from STDIN until given delimiter is found (or EOF since we can't do
		anything about it), then return the fd for the next program to read from

	input_filename is just the thing we found right after our operator, so in the
		case of '<<' even though it's not a filename, it's already the value that
		we want (it's the delimiter but it has the right value)

	Create a pipe so it's easier to handle the fd
	Write into it after the check, so that if the line matches, it is not
		included

	closing the pipe will automatically write EOF into it

	Also write a \n between each line as bash does
*/
int	read_until_delimiter(char *delimiter)
{
	char	*line;
	int		match;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("Pipe error while waiting for delimiter");
	match = 0;
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(delimiter, line) == 0)
		{
			match = 1;
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		line = readline("> ");
	}
	close(pipe_fd[1]);
	if (!match)
		printf("Warning, EOF encountered while waiting for '%s'\n", delimiter);
	return (pipe_fd[0]);
}
