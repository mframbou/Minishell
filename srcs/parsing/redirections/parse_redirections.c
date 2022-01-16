/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 15-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 16-01-2022 20:20 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Simply returns the length of tha redirection operator (<, <<, > or >>)
*/
static int	get_redirection_chars_len(char *op_index)
{
	char	first;
	char	second;

	first = '\0';
	second = '\0';
	if (op_index[0] != '\0')
	{
		first = op_index[0];
		if (op_index[1] != '\0')
			second = op_index[1];
	}
	if (first == '>' || first == '<')
	{
		if (second == first)
			return (2);
		return (1);
	}
	return (0);
}

/*
	Opens the file according to the redirection type and returns the fd
*/
static int	open_file_for_redirection(char *filename, int redirection_type)
{
	int	fd;
	int	flags;
	int	mode;

	mode = 0;
	if (redirection_type == SINGLE_LEFT_REDIRECT || \
	redirection_type == DOUBLE_LEFT_REDIRECT)
		flags = O_RDONLY;
	else if (redirection_type == SINGLE_RIGHT_REDIRECT)
	{
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		mode = 0666;
	}
	else if (redirection_type == DOUBLE_RIGHT_REDIRECT)
	{
		flags = O_CREAT | O_WRONLY | O_APPEND;
		mode = 0666;
	}
	else
		return (-1);
	return (open(filename, flags, mode));
}

static int	get_filename_length(char *filename)
{
	int	j;

	j = 0;
	while (filename[j] && \
	!(ft_isspace(filename[j]) || !is_valid_in_filename(filename[j])))
	{
		if (filename[j] == '"' || filename[j] == '\'')
			j += is_closed_quote(&(filename[j]));
		j++;
	}
	return (j);
}

/*
	Takes pointer to line
	get_next_redirect_operator_index returns either the good index, or the index
	of the end of the string ('\0')

	- If we find a redirection, retrieve the type and skip the operator,
		then retrieve the next argument which is the filename,
		the end of the filename is marked by either a space or an invalid char
		(pipe etc.) except if it's in quotes
	- Remove the extracted string + the operator from the line, and put
		the type in the int pointed by argument, and return the filename
		we don't call substr on i,j because we need to remove '>> + filename'
		and not just filename

	Extract the filename and remove it from the line

	"echo > test.txt" => Return: "test.txt", line = "echo"

	Takes pointer to line string (because it removes the filename)
	and pointer to redirection type, which is set if any is found
*/
static char	*get_first_redirection_filename(char **line, int *redirection_type)
{
	int		i;
	int		j;
	char	*filename;

	filename = NULL;
	i = get_next_redirect_operator_index((*line), 0);
	if ((*line)[i])
	{
		*redirection_type = get_next_redirect_operator_type((*line), 0);
		i += get_redirection_chars_len(&((*line)[i]));
		while ((*line)[i] && ft_isspace((*line)[i]))
			i++;
		if (!(*line)[i])
		{
			printf("TODO NO FILENAME\n");
			return (NULL);
		}
		filename = &((*line)[i]);
		filename = ft_substr(filename, 0, get_filename_length(filename));
		remove_substr_from_string(line, \
								get_next_redirect_operator_index((*line), 0), \
								i + j);
	}
	return (filename);
}

/*
	Takes pointer to program line (eg. "echo 'pouet $HOME' > test.txt") and:
	- extract redirections (new line = "echo 'pouet $HOME'")
		put in the redirection structure in argument
		(fd (x), filename ("test.txt") and type('>'))
	Do this while we found a redirection (everytine we remove one, so if
		we find a new one, close the previous one, this keeps the last one
		opened)
	
	Return value:
		-1 = Error
		0 = Success
		1 = No filename found (no redirections in program)
*/
int	parse_redirectoins_and_create_files(char **line, t_redirection *redirection)
{
	redirection->type = 0;
	redirection->filename = NULL;
	redirection->fd = -1;
	redirection->filename = get_first_redirection_filename(line, \
															&redirection->type);
	redirection->fd = -1;
	while (redirection->filename)
	{
		redirection->filename = interpret_env_args(redirection->filename);
		interpret_quotes(&redirection->filename);
		redirection->fd = open_file_for_redirection(redirection->filename, \
													redirection->type);
		if (redirection->fd == -1)
		{
			perror("TODO: FREE EVERYTHING Error while opening file");
			return (-1);
		}
		redirection->filename = get_first_redirection_filename(line, \
															&redirection->type);
		if (redirection->filename)
			close(redirection->fd);
	}
	if (redirection->fd != -1)
		return (0);
	return (1);
}
