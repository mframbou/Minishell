/* ************************************************************************** */

/*                                                                           */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created:   by            `-'                        `-'                  */
/*   Updated:   by                                                            */
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

static int	perror_return(char *str)
{
	perror(str);
	return (-2);
}

typedef void (*builtin_ptr)(char **args, int output_fd);

builtin_ptr	get_builtin_function(char *name)
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
	char		**env;
	builtin_ptr builtin_func;
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
			return (perror_return("pipe failure"));
	// env = get_env_as_string_array(); I don't know if we should send env to functions, need to check
	// free_ft_split(env);
	builtin_func = get_builtin_function(args[0]);
	if (builtin_func)
		builtin_func(args, pipe_fd[1]);
	close(pipe_fd[1]);
	return(pipe_fd[0]);
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
	//free_ft_split(env);
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


static int	execute_program_from_args_and_fd(int read_fd, char *program_path, \
											char **args)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror_return("pipe failure"));
	else
	{
		if (fork() == 0)
		{
			dup2(read_fd, STDIN_FILENO);
			close(read_fd);
			exec_and_redirect_stdout(pipe_fd, program_path, args);
			return (-2);
		}
		else
		{
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

int execute_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*curr;
	int		read_fd;
	int		new_read_fd;
	char	*program;
	char	buf;

	curr = cmd_lst;
	read_fd = -1;
	new_read_fd = -1;
	while (curr)
	{
		if (is_builtin(curr->args[0]))
		{
			new_read_fd = execute_builtin(curr->args);
		}
		else
		{
			program = is_program_in_path(curr->args[0]);
			if (program)
			{
				new_read_fd = execute_program(read_fd, program, curr->args);
				if (new_read_fd == -2)
				{
					printf("An error occured while executing pipeline\n");
					return (-2);
				}
			}
		}
		if (read_fd >= 0)
			close(read_fd);
		read_fd = new_read_fd;
		curr = curr->next;
	}
	//printf("current print fd: %d\n", read_fd);
	while (read(read_fd, &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);
	close(read_fd);
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
