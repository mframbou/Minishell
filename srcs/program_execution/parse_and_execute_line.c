/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 22-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 26-01-2022 13:10 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_cmd_lst(int read_fd, t_cmd *cmd_lst);
int			execute_one_cmd(t_cmd *cmd, int read_fd);

static int	has_only_one_command(t_cmd *cmd_lst)
{
	if (cmd_lst->next)
		return (0);
	return (1);
}

/*
	Executes the commands in the line, sends info to stdin from 'read_fd' if != -1
	Returns the read_fd of the last command of the line

	First call will be with input_read_fd = -1, but then it will
	be recursively called
*/

int	parse_and_execute_line(int input_read_fd, char *line)
{
	t_cmd	*cmd_list;
	int		output_read_fd;
	int		syntax_error_index;

	if (are_parentheses_invalid(line))
		return (-2);
	if (has_syntax_error(line))
	{
		syntax_error_index = has_syntax_error(line) - 1;
		printf("Syntax error near index %d in '%s' ('%c')\n", \
													syntax_error_index, \
													line, \
													line[syntax_error_index]);
		return (-2);
	}
	cmd_list = parse_cmds(line);
	if (cmd_list)
		output_read_fd = execute_cmd_lst(input_read_fd, cmd_list);
	clear_cmd_list(&cmd_list);
	return (output_read_fd);
}

/*
	Takes pointer to current command, modifies it if needed

	- Wait for last process and save exit status
	- Wait for all other but don't save exit status
	- Since it's not a pipe, redirect all the current pipe to stdout (flush)

	Then check the status and execute accordingly:
		- if AND and exit status != 0, skip next command
		- if OR and exit status == 0, skip next command

		We check if there is a command after first skip but it really shouldn't
		be true since we checked if layout was valid earlier

		/!\ only skip once because in our main loop we do curr = curr.next
		so it will already skip it

	Don't check for waitpid == -1 because if there are no childs,
	like only builtins, it will return -1 but we don't want to catch that
*/
static int	execute_and_and_or_if_needed(t_cmd **cmd, int read_fd)
{
	t_cmd	*curr;
	int		exit_status;

	curr = *cmd;
	if (curr->next_cmd_operator == AND_CHAR || \
		curr->next_cmd_operator == OR_CHAR)
	{
		if (waitpid(g_pid, &exit_status, 0) != -1)
			set_exit_status(exit_status);
		while (wait(NULL) > 0)
			;
		flush_pipe(read_fd);
		read_fd = -1;
		if ((curr->next_cmd_operator == AND_CHAR && *get_exit_status() != 0) || \
			(curr->next_cmd_operator == OR_CHAR && *get_exit_status() == 0))
		{
			*cmd = curr->next;
		}
	}
	return (read_fd);
}

/*
	read_fd = fd to read from for next command
	new_read_fd = fd the first command has written to

	"sleep 4 | echo test && echo salut" will execute normaly sleep and echo test
	then wait for them and when they are all finished execute the && or the ||

	so need to wait for all childrens before doing && or ||

	if parentheses, don't close the read fd because recursive call will need it

	exit only if exit is the only function
*/
static int	execute_cmd_lst(int read_fd, t_cmd *cmd_lst)
{
	t_cmd	*curr;
	int		new_read_fd;
	char	*program;
	char	buf;
	int		exit_status;

	curr = cmd_lst;
	new_read_fd = -1;
	while (curr)
	{
		read_fd = execute_one_cmd(curr, read_fd);
		read_fd = execute_and_and_or_if_needed(&curr, read_fd);
		if (read_fd == -2)
			return (-2);
		curr = curr->next;
		if (should_exit() && has_only_one_command(cmd_lst))
		{
			clean_exit(read_fd);
		}
		set_should_exit(0);
	}
	return (read_fd);
}
