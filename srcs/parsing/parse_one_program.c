/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 17:01 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Takes pointer to array of string (triple pointer)
	the interpret the arguments (ex echo $USER => echo walidou)
*/
void	interpret_all_args(char	***args)
{
	int	i;

	i = 0;
	while ((*args)[i])
	{
		(*args)[i] = interpret_env_args((*args)[i]);
		i++;
	}
}

/*
	get_one_arg moves the index directly to the end of the interpreted arg
*/
static int	count_args(char *line)
{
	int		i;
	char	*current_arg;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		current_arg = get_one_arg(line, &i);
		if (current_arg)
		{
			count++;
			ft_free(current_arg);
		}
	}
	return (count);
}

char	**remove_empty_args(char **args)
{
	int		valid_count;
	int		i;
	int		j;
	char	**new_args;

	valid_count = 0;
	i = -1;
	while (args[++i])
		if (args[i][0] != '\0')
			valid_count++;
	new_args = (char **) ft_malloc(sizeof (char *) * (valid_count + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			new_args[j++] = args[i];
		else
			ft_free(args[i]);
		i++;
	}
	ft_free(args);
	new_args[j] = NULL;
	return (new_args);
}

/*
	get_one_arg moves the index to the end of the parsed arg so
		no need to do i += ft_strlen(current_arg)
*/
void	fill_args_of_one_program(char *program, char **args)
{
	int		i;
	int		argc;
	char	*current_arg;

	i = 0;
	argc = 0;
	while (program[i])
	{
		while (program[i] && ft_isspace(program[i]))
			i++;
		if (!program[i])
			break ;
		current_arg = get_one_arg(program, &i);
		if (current_arg)
			args[argc++] = current_arg;
	}
	args[argc] = NULL;
}

/*
	This takes a line (right not not the full line but only 1 progran 
		(split on pipes))
	(for instance "echo -e -n Salut ceci "est un test" "The USER is $USER"")

	and returns it as a parsed string array :
	["echo", "-e", "-n", "Salut", "ceci", "est un test", "The USER is mframbou"]

	Interpret ENV ($)
*/
char	**parse_program_and_args(char *line)
{
	char			**args;
	char			*current_arg;
	char			*new_line;

	new_line = ft_strtrim(line, " \t\v\f\r");
	ft_free(line);
	args = (char **) ft_malloc(sizeof(char *) * (count_args(new_line) + 1));
	if (!args)
		return (NULL);
	fill_args_of_one_program(new_line, args);
	ft_free(new_line);
	interpret_all_args(&args);
	args = remove_empty_args(args);
	return (args);
}
