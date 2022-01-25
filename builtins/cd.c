/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 14:03 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	If no arguments, cd to home, if no home, print error

	Return values:
	0 = Success
	1 = Other error / HOME does not exists
*/
void	cd_command(char *argv[], int output_fd)
{
	int		res;

	res = 0;
	if (argv[1] == NULL)
	{
		if (get_env_variable("HOME"))
			res = chdir(get_env_variable("HOME"));
		else
		{
			ft_putstr_fd("cd: HOME not set\n", output_fd);
			set_exit_status(EXIT_FAILURE);
			return ;
		}
	}
	else
		res = chdir(argv[1]);
	if (res == -1)
	{
		set_exit_status(errno);
		ft_putstr_fd("cd: ", output_fd);
		ft_putstr_fd(argv[1], output_fd);
		ft_putstr_fd(strerror(errno), output_fd);
	}
	else
		set_exit_status(EXIT_SUCCESS);
}
