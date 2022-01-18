/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 18-01-2022 22:24 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_command(char *argv[], int output_fd)
{
	int		res;
	char	*home_path;

	res = 0;
	if (argv[1] == NULL)
	{
		home_path = getenv("HOME");
		if (home_path)
			res = chdir(home_path);
	}
	else
		res = chdir(argv[1]);
	if (res == -1)
	{
		perror(argv[1]);
		//ft_putstr_fd(MINISHELL_PROMPT, output_fd);
		//ft_putstr_fd("cd: ", output_fd);
		//ft_putstr_fd(argv[1], output_fd);
		//ft_putstr_fd(strerror(errno), output_fd);
	}
}
