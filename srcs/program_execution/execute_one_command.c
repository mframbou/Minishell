/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 25-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 26-01-2022 13:08 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Takes current fd and return either a new fd (if redirection)
	or the same if there is no redirection (input so < and <<)

	If an input redirection is found, close the previous fd if != -1
*/
static int	get_fd_for_input_redirection_if_any(int current_fd, \
												t_redirection *redir)
{
	int	fd;

	fd = current_fd;
	if (redir->in_filename)
	{
		if (redir->in_redir_type == SINGLE_LEFT_REDIRECT)
		{
			close(current_fd);
			fd = open_file_for_redirection(redir->in_filename, \
											redir->in_redir_type);
			if (fd == -1)
				return (-2);
		}
		else if (redir->in_redir_type == DOUBLE_LEFT_REDIRECT)
		{
			close(current_fd);
			fd = read_until_delimiter(redir->in_filename);
		}
	}
	return (fd);
}

/*
	Returns next read fd, or -2 on error

	If command failed, break the pipeline, don't flush it but just close it,
	echo test | pouet should not print "test"
*/
static int	execute_program_if_found(char **args, int read_fd)
{
	char	*program;

	if (is_builtin(args[0]))
		read_fd = execute_builtin(args);
	else
	{
		if (has_slash(args[0]))
			program = search_absolute_path_program(args[0]);
		else
			program = is_program_in_path(args[0]);
		if (!program)
		{
			perror(args[0]);
			close(read_fd);
			return (-2);
		}
		read_fd = execute_program(read_fd, program, args);
		set_terminal_attributes(ECHOCTL_ON);
		if (read_fd == -2)
			perror("An error occured while executing pipeline:");
		if (read_fd == -2)
			return (-2);
		ft_free(program);
	}
	return (read_fd);
}

/*
	Returns next fd to read from, either read_fd or -1 if redirection is found
*/
static int	redirect_output_if_needed(t_cmd *cmd, int read_fd)
{
	int		fd;
	char	buf;

	if (cmd->redirection.out_filename)
	{
		fd = open_file_for_redirection(cmd->redirection.out_filename, \
										cmd->redirection.out_redir_type);
		if (fd == -1)
		{
			perror("Error while opening file for writing");
			return (-2);
		}
		while (read(read_fd, &buf, 1) > 0)
			write(fd, &buf, 1);
		close(fd);
		close(read_fd);
		read_fd = -1;
	}
	return (read_fd);
}

/*
	Don't break the pipeline if a file is invalid for instance
	only break it on execve failure

	if (new_read_fd == -2) only happens in case of missing file or file error,
		we shouldn't break the pipeline in this case, so just reset read_fd
*/
int	execute_one_cmd(t_cmd *cmd, int read_fd)
{
	int	new_read_fd;

	if (cmd->parentheses_content)
	{
		new_read_fd = parse_and_execute_line(read_fd, cmd->parentheses_content);
		if (new_read_fd == -2)
			return (-1);
		return (new_read_fd);
	}
	read_fd = get_fd_for_input_redirection_if_any(read_fd, &cmd->redirection);
	if (read_fd == -2)
	{
		perror("An error occured while opening file:");
		read_fd = -1;
	}
	new_read_fd = execute_program_if_found(cmd->args, read_fd);
	if (read_fd >= 0)
		close(read_fd);
	if (new_read_fd == -2)
		return (-2);
	read_fd = redirect_output_if_needed(cmd, new_read_fd);
	if (read_fd == -2)
		return (-2);
	return (read_fd);
}
