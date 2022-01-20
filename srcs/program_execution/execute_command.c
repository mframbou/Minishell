/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 20-01-2022 22:52 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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

int	perror_return(char *str)
{
	perror(str);
	return (-2);
}

typedef void	(*t_builtin_ptr)(char **args, int output_fd);

t_builtin_ptr	get_builtin_function(char *name)
{
	if (strcmp(name, "echo") == 0)
		return (&echo_command);
	else if (strcmp(name, "export") == 0)
		return (&export_command);
	else if (strcmp(name, "unset") == 0)
		return (&unset_command);
	else if (strcmp(name, "env") == 0)
		return (&env_command);
	else if (strcmp(name, "cd") == 0)
		return (&cd_command);
	else if (strcmp(name, "pwd") == 0)
		return (&pwd_command);
	else if (strcmp(name, "exit") == 0)
		return (&exit_command);
	else
		return (NULL);
}

int	execute_builtin(char **args)
{
	char			**env;
	t_builtin_ptr	builtin_func;
	int				pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror_return("pipe failure"));
	(void) env;
	// TODO env = get_env_as_string_array(); I don't know if we should send env to functions, need to check
	// free_ft_split(env);
	builtin_func = get_builtin_function(args[0]);
	if (builtin_func)
		builtin_func(args, pipe_fd[1]);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/*
	pipe[0] = read
	pipe[1] = write

	dup2 makes arg2 "redirect" to arg1
	so dup2(FD, STDOUT) redirects STDOUT to FD

	Returns the pipe read fd for next pipe
*/

/*
int	execute_program(int input_fd, char *program_path, char **args)
{
	int		pipe_success;
	int		pipe_fd[2];
	char	**env;

	if (pipe(pipe_fd) == -1)
	{
		printf("erreur pipe");
		return (-1);
	}
	if (fork() == 0)
	{
		// Capture STDOUT and redirect to pipe output (so write to pipe input)
		close(pipe_fd[0]); // We only write so close READ end
		
		dup2(pipe_fd[1], STDOUT_FILENO);
		env = get_env_as_string_array();
		//free_ft_split(env);
		close(pipe_fd[1]);
		execve(program_path, args, env);
		
	}
	else
	{
		close(pipe_fd[1]); // We only read so close WRITE end
		//printf("Pipe redirecting ...\n");
		char buf;

		// test redirecting to another pipe to simulate piping
		//int pipe_fd2[2];
		//
		//pipe(pipe_fd2);
		//if (fork() == 0)
		//{
		//	close(pipe_fd2[1]);
//
		//	while (read(pipe_fd2[0], &buf, 1) > 0)
		//	{
		//		write(STDOUT_FILENO, &buf, 1);
		//	}
		//	close(pipe_fd2[0]);
		//}
		//else
		//{
		//	close (pipe_fd2[0]);
		//	while (read(pipe_fd[0], &buf, 1) > 0)
		//		write(pipe_fd2[1], &buf, 1);
		//	close(pipe_fd2[1]);
		//}
		while (read(pipe_fd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		close(pipe_fd[0]);
		//dup2(STDOUT_FILENO, pipe_fd[0]);
		// Do things
		//close(pipe_fd[0]);
	}
}
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
		return (perror_return("dup2 failure"));
	}
	env = get_env_as_string_array();
	//free_ft_split(env) TODO;
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
*/
int	execute_program(int input_fd, char *program_path, char **args)
{
	int	output_read_fd;
	int	exit_status;

	output_read_fd = -1;
	if (input_fd == -1)
	{
		output_read_fd = execute_program_from_args(program_path, args);
		if (output_read_fd == -2)
		{
			// Error already printed out
			return (-2);
		}
	}
	else
	{
		output_read_fd = execute_program_from_args_and_fd(input_fd, program_path, args);
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
	/*printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();*/
	if (!match)
		printf("Warning, EOF encountered while waiting for '%s'\n", delimiter);
	return (pipe_fd[0]);
}

static int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '/')
			return (1);
	return (0);
}

/*
	If file doesn't exists / is not a regular file or a symlink, we don't
	consider it as executable

	stat function directly use the file pointed by the symlink if any,
	so we don't need to check if it is a symlink, then if the file it points
	to is a regular file

	Macros S_ISREG and S_ISLNK help doing it instead of doing binary operations
	S_IXUSR = permission bit for execution
*/
int	is_regular_file_or_symlink(char *file)
{
	struct stat	file_infos;
	int			stat_return;

	stat_return = stat(file, &file_infos);


	if (stat_return == -1 \
	|| !S_ISREG(file_infos.st_mode) \
	|| !(__S_IEXEC & file_infos.st_mode))
	{
		return (0);
	}
	return (1);
}

/*
	https://pubs.opengroup.org/onlinepubs/9699919799/utilities/
	V3_chap02.html#tag_18_09_01_01

	If the command name contains at least one <slash>, the shell shall execute 
	the utility in a separate utility environment with actions equivalent 
	to calling the execl() function

	If we have a '/' in the filename, then execute it as absolute / relative
		path. But if there isn't any slashes, just search in PATH

	S_IFMT = Bit mask for file type, used to only keep the file types of
		stat.st_mode structure
	If file is different from symlink or regular file, dont execute it
*/
char	*search_absolute_path_program(char *program)
{
	char		*res;
	struct stat	file_infos;

	if (!is_regular_file_or_symlink(program) || !has_slash(program))
		return(NULL);
	return (ft_strdup(program));
}

/*
	read_fd = fd to read from for next command
	new_read_fd = fd the first command has written to
*/
int execute_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*curr;
	int		read_fd;
	int		new_read_fd;
	char	*program;
	char	buf;
	int		exit_status;
	int		waitpid_count = 0;
	int		cmd_count = 0;

	curr = cmd_lst;
	read_fd = -1;
	new_read_fd = -1;
	while (curr)
	{
		cmd_count++;
		if (curr->redirection.in_filename != NULL)
		{
			if (curr->redirection.in_redir_type == SINGLE_LEFT_REDIRECT)
			{
				int fd = open_file_for_redirection(curr->redirection.in_filename, curr->redirection.in_redir_type);
		
				if (fd == -1)
				{
					return (-1);
				}
				read_fd = fd;
			}
			else if (curr->redirection.in_redir_type == DOUBLE_LEFT_REDIRECT)
			{
				read_fd = read_until_delimiter(curr->redirection.in_filename);
			}
		}
		if (is_builtin(curr->args[0]))
		{
			new_read_fd = execute_builtin(curr->args);
		}
		else
		{
			program = is_program_in_path(curr->args[0]);
			if (program)
			{
				waitpid_count++;
				new_read_fd = execute_program(read_fd, program, curr->args);
				if (new_read_fd == -2)
				{
					printf("An error occured while executing pipeline\n");
					return (-2);
				}
			}
			else
			{
				waitpid_count++;
				program = search_absolute_path_program(curr->args[0]);
				if (program)
				{
					new_read_fd = execute_program(read_fd, program, curr->args);
				}
				else
				{
					
					printf("We did not find any command matchig this sir.\n");
				}
			}
			free(program);
		}
		if (read_fd >= 0)
			close(read_fd);
		read_fd = new_read_fd;
		if (curr->redirection.out_filename != NULL)
		{
			int fd = open_file_for_redirection(curr->redirection.out_filename, curr->redirection.out_redir_type);
			if (fd == -1)
			{
				perror("Error while opening file for writing");
				return (-2);
			}
			while (read(new_read_fd, &buf, 1) > 0)
				write(fd, &buf, 1);
			new_read_fd = -1;
			read_fd = -1;
		}
		if (curr->next)
		{
			// WNOHANG make the waitpid non blocking, which solve the issue of multiple blocking commands piping
			// eg. cat | cat, instead of waiting for 1st cat to complete, both are executed at the same time
			//if (g_pid)
			//{
			//	waitpid(g_pid, &exit_status, WNOHANG); // If it's the last command, first redirect to stdout, then waitpid (if we do just "cat" for instance it should print before waiting)
			//	set_exit_status(exit_status);
			//}
		}
		curr = curr->next;

		if (should_exit() && cmd_count == 1 && !curr) // Only exit if it's the only command
		{
			clear_cmd_list();
			flush_pipe(read_fd);
			free_redirections();
			rl_clear_history();
			printf("Exit status is %d\n", *get_exit_status());
			exit(*get_exit_status());
			
		}
		else if (should_exit())
		{
			set_should_exit(0);
		}
	}
	//WEXITSTATUS
	free_redirections();
	flush_pipe(read_fd);
	if (g_pid)
	{
		waitpid(g_pid, &exit_status, 0); // Wait to get the last process exit code
		set_exit_status(exit_status);
	}
	for (int i = 0; i < waitpid_count; i++)
		waitpid(-1, &exit_status, 0); // Wait for all childrens at the end, each waitpid only waits for 1 children
	if (g_pid || waitpid_count)	// If we only executed builtins for instance, don't set since it's already done
		set_exit_status(exit_status);
	//printf("Finished waiting\n");
	g_pid = 0;
	return (0);
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
