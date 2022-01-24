/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:39 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
			//free(current_arg);
			//i += ft_strlen(current_arg);
		}
	}

	//char	*current_arg;
	//char	*line;
	//int		i;
	//int		count;
	//
	//i = 0;
	//count = 0;
	//line = ft_strtrim(old_line, " \t\v\f\r");
	//while (line[i])
	//{
	//	while (line[i] && ft_isspace(line[i]))
	//		i++;
	//	if (!line[i])
	//		break ;
	//	current_arg = get_one_arg(line, &i);
	//	if (current_arg)
	//	{
	//		i += ft_strlen(current_arg);
	//		count++;
	//		//free(current_arg);
	//	}		
	//}
	////free(line);
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
		//else
			//free(args[i]);
		i++;
	}
	//free(args);
	new_args[j] = NULL;
	return (new_args);
}

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
		{
			args[argc++] = current_arg;
			//i += ft_strlen(current_arg);
		}
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
	//free(line);
	args = (char **) ft_malloc(sizeof(char *) * (count_args(new_line) + 1));
	if (!args)
		return (NULL);
	fill_args_of_one_program(new_line, args);
	//free(new_line);
	interpret_all_args(&args);
	args = remove_empty_args(args);
	return (args);
}
