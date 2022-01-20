/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 19-01-2022 14:57 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "environment.h"

/*
	Check arg validity
	If not a single string, split on '='
	Set key / value

	if we have a '=', value is everything after the said =
*/
void	export_command(char *argv[], int output_fd)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	int		failure;

	i = 1;
	failure = 0;
	while (argv[i])
	{
		j = 0;
		if (ft_isalpha(argv[i][j]) || argv[i][j] == '_')
			j++;
		else
		{
			printf("export: '%s': not an identifier\n", argv[i]);
			set_exit_status(EXIT_FAILURE);
			i++;
			continue ;
		}
		while (argv[i][j] && (ft_isalnum(argv[i][j]) || argv[i][j] == '_'))
			j++;
		name = ft_substr(argv[i], 0, j);
		if (!argv[i][j])
			value = NULL;
		else if (argv[i][j] == '=')
			value = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j + 1);
		else
		{
			printf("export: '%s': not an identifier\n", argv[i]);
			set_exit_status(EXIT_FAILURE);
			i++;
			continue ;
		}
		if (value)
			add_env_variable(name, value);
		else
			add_env_variable(name, ft_strdup(""));
		i++;
	}
	if (!failure)
		set_exit_status(EXIT_SUCCESS);
}
