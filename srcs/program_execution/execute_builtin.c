/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 25-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 14:48 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	builtin_func = get_builtin_function(args[0]);
	if (builtin_func)
		builtin_func(args, pipe_fd[1]);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
