/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 20-01-2022 15:22 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	0 = Success
	1 = Other error / HOME does not exists
*/
void	cd_command(char *argv[], int output_fd)
{
	int		res;
	char	*home_path;

	res = 0;
	if (argv[1] == NULL)
	{
		home_path = get_env_variable("HOME");
		if (home_path)
			res = chdir(home_path);
		else
		{
			printf("cd: HOME not set\n");
			set_exit_status (EXIT_FAILURE);
			return ;
		}
	}
	else
		res = chdir(argv[1]);
	if (res == -1)
	{
		set_exit_status(errno);
		perror(argv[1]);
		//ft_putstr_fd(MINISHELL_PROMPT, output_fd);
		//ft_putstr_fd("cd: ", output_fd);
		//ft_putstr_fd(argv[1], output_fd);
		//ft_putstr_fd(strerror(errno), output_fd);
	}
	else
		set_exit_status(EXIT_SUCCESS);
}
