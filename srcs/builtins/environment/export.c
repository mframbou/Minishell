/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 27-01-2022 13:50 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "environment.h"

static void	print_invalid_identifier_and_set_exit_status(char *identifier, \
														int output_fd)
{
	ft_putstr_fd("export: '", output_fd);
	ft_putstr_fd(identifier, output_fd);
	ft_putstr_fd("': not an identifier\n", output_fd);
	set_exit_status(EXIT_FAILURE);
}

static char	*parse_name(char *str, int *index, int *failure, int output_fd)
{
	char	*name;

	name = NULL;
	if (ft_isalpha(str[*index]) || str[*index] == '_')
		(*index)++;
	else
	{
		print_invalid_identifier_and_set_exit_status(str, output_fd);
		*failure = 1;
		return (NULL);
	}
	while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
		(*index)++;
	name = ft_substr(str, 0, *index);
	return (name);
}

static char	*parse_value(char *str, int index, int *failure, int output_fd)
{
	char	*value;

	if (!str[index])
		value = NULL;
	else
	{
		if (str[index] == '=')
			value = ft_substr(str, index + 1, ft_strlen(str) - index + 1);
		else
		{
			print_invalid_identifier_and_set_exit_status(str, output_fd);
			*failure = 2;
			return (NULL);
		}
	}
	return (value);
}

static int	export_one_arg(char *arg, int *failure, int output_fd)
{
	int		i;
	char	*value;
	char	*name;

	i = 0;
	name = parse_name(arg, &i, failure, output_fd);
	if (!name)
		return (-1);
	value = parse_value(arg, i, failure, output_fd);
	if (*failure)
	{
		i++;
		*failure = 1;
		ft_free(name);
		return (-1);
	}
	if (value)
		add_env_variable(name, value);
	else
		add_env_variable(name, ft_strdup(""));
	return (0);
}

/*
	Check arg validity
	If not a single string, split on '='
	Set key / value

	if we have a '=', value is everything after the said =
	when one is invalid, just skip it
*/
void	export_command(char *argv[], int output_fd)
{
	int		i;
	int		failure;

	i = 1;
	failure = 0;
	while (argv[i])
	{
		export_one_arg(argv[i], &failure, output_fd);
		i++;
	}
	if (!failure)
		set_exit_status(EXIT_SUCCESS);
}
