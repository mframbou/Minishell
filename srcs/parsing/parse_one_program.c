/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 13-01-2022 16:53 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Takes pointer to array of string (triple pointer)
	the interpret the arguments (ex echo $USER => echo walidou)
*/
static void	interpret_all_args(char	***args)
{
	int	i;

	i = 0;
	while ((*args)[i])
	{
		(*args)[i] = interpret_env_arg((*args)[i]);
		i++;
	}
}

static int	count_args(char *old_line)
{
	char	*current_arg;
	char	*line;
	int		i;
	int		count;

	i = 0;
	count = 0;
	line = ft_strtrim(old_line, " \t\v\f\r");
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		current_arg = get_one_arg(line, &i);
		if (current_arg)
		{
			i += ft_strlen(current_arg);
			count++;
			free(current_arg);
		}		
	}
	free(line);
	return (count);
}

static char	**remove_empty_args(char **args)
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
	new_args = (char **) malloc(sizeof (char *) * (valid_count + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			new_args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	free(args);
	new_args[j] = NULL;
	return (new_args);
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
	char	**args;
	char	*current_arg;
	char	*new_line;
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	args = (char **) malloc(sizeof(char *) * (count_args(line) + 1));
	if (!args)
		return (NULL);
	new_line = ft_strtrim(line, " \t\v\f\r");
	free(line);
	while (new_line[i])
	{
		while (new_line[i] && ft_isspace(new_line[i]))
			i++;
		if (!new_line[i])
			break ;
		current_arg = get_one_arg(new_line, &i);
		if (current_arg)
		{
			args[argc++] = current_arg;
			i += ft_strlen(current_arg);
		}
	}
	args[argc] = NULL;
	interpret_all_args(&args);
	args = remove_empty_args(args);
	return (args);
}
