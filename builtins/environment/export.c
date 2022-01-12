/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 12-01-2022 18:38 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "environment.h"

/*
	Check arg validity
	If not a single string, split on '='
	Set key / value
*/
void	export_command(char *argv[], int output_fd)
{
	char	**values;
	int		i;

	i = 1;
	while (argv[i])
	{
		values = ft_split(argv[i], '=');
		if (!values || !values[0])
		{
			free_ft_split(values);
			ft_putstr_fd("Invalid syntax\n", output_fd);
		}
		if (values[1])
			add_env_variable(ft_strdup(values[0]), ft_strdup(values[1]));
		else
			add_env_variable(ft_strdup(values[0]), ft_strdup(""));
		free_ft_split(values);
		i++;
	}
}
