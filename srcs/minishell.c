/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 20-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 27-01-2022 12:44 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

void	init_basic_env_variables(void)
{
	char	*home_env;
	char	*path_env;

	home_env = getenv("HOME");
	path_env = getenv("PATH");
	if (home_env)
		add_env_variable(ft_strdup("HOME"), ft_strdup(home_env));
	else
		add_env_variable(ft_strdup("HOME"), ft_strdup("/"));
	if (path_env)
		add_env_variable(ft_strdup("PATH"), ft_strdup(path_env));
	else
		add_env_variable(ft_strdup("PATH"), ft_strdup(PATH_STR));
}

/*
	Changes between ECHOCTL terminal and not

	current values:
	0 : not initialized
	1 : old (ECHOCTL enabled)
	2 = new (ECHOCTL disabled)

	C boolean values are always either 0 or 1

	control == -1 is true if minisell in minishell for instance
*/
void	set_terminal_attributes(int term_type)
{
	static struct termios	old;
	static struct termios	new;
	static int				initialized = 0;
	int						control;

	if (!initialized)
	{
		control = tcgetattr(STDOUT_FILENO, &old);
		if (control == -1)
			return ;
		new = old;
		new.c_lflag &= ~ECHOCTL;
		old.c_lflag |= ECHOCTL;
		initialized = 1;
	}
	if (term_type == ECHOCTL_ON)
		control = tcsetattr(STDOUT_FILENO, TCSANOW, &old);
	else if (term_type == ECHOCTL_OFF)
		control = tcsetattr(STDOUT_FILENO, TCSANOW, &new);
	if (control == -1)
	{
		perror("tcsetattr error");
		ft_free_all();
		exit (EXIT_FAILURE);
	}
}

static int	execute_line(char *line)
{
	int	res;
	int	exit_status;

	if (!line || line[0] == '\0' || is_line_empty(line))
		return (0);
	add_history(line);
	if (are_parentheses_invalid(line))
		return (-1);
	if (has_syntax_error(line))
	{
		printf("Syntax error near index %d ('%c')\n", \
		has_syntax_error(line) - 1, line[has_syntax_error(line) - 1]);
		return (-1);
	}
	res = parse_and_execute_line(-1, line);
	if (res == -2)
		return (-1);
	exit_status = 0;
	if (res >= 0)
		flush_pipe(res);
	if (g_pid != 0 && waitpid(g_pid, &exit_status, 0) != -1)
		set_exit_status(exit_status);
	while (wait(NULL) > 0)
		;
	return (0);
}

/*
	Au final tous les double quotes sont supprimés,
	sauf si ils sont dans des simples quotes

	- Parse line, execute commands
	- Flush pipe
	- Wait for last process to get exit status and wait for all others
	but don't care about exit status.

	- If syntax error, continue since it's already printed out
*/
int	main(int argc, char **argv)
{
	char	*line;
	t_cmd	*cmd_list;
	int		exit_status;

	init_signals();
	set_terminal_attributes(ECHOCTL_OFF);
	init_basic_env_variables();
	set_exit_status(0);
	while (1)
	{
		line = readline(MINISHELL_PROMPT);
		if (line == NULL)
			clean_exit(-1);
		if (execute_line(line) == -1)
			continue ;
		set_terminal_attributes(ECHOCTL_OFF);
		g_pid = 0;
	}
	clean_exit(-1);
}
