/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 12-01-2022 18:37 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_command(char **argv, int output_fd)
{
	int	print_nl;
	int	i;
	int	argc;

	i = 1;
	print_nl = 1;
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc >= 2 && ft_strcmp(argv[i], "-n") == 0)
	{
		i++;
		print_nl = 0;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], output_fd);
		i++;
		if (i != argc)
			ft_putchar_fd(' ', output_fd);
	}
	if (print_nl)
		ft_putchar_fd('\n', output_fd);
}
