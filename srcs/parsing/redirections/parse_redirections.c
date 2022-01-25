/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 15-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 13:30 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

	- If we find a redirectio, retrieve the type and skip the operator, 
		then retrieve the next argument which is the filename
		The end of the filename is marked by either a space or an invalid char
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
static char	*get_first_redirection_filename(char **line, int *redir_type)
{
	int		i;
	int		j;
	char	*filename;

	filename = NULL;
	i = get_next_redirect_operator_index((*line), 0);
	if ((*line)[i])
	{
		*redir_type = get_next_redirect_operator_type((*line), 0);
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
								i + ft_strlen(filename));
	}
	return (filename);
}

/* OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD OLD
int	parse_redirections_and_create_files(char **line, t_redirection *redir)
{
	init_redirection_struct(redir);
	redir->out_filename = get_first_redirection_filename(line, \
														&redir->out_redir_type);
	while (redir->out_filename)
	{
		redir->out_filename = interpret_env_args(redir->out_filename);
		interpret_quotes(&redir->out_filename);
		redir->out_fd = open_file_for_redirection(redir->out_filename, \
													redir->out_redir_type);
		if (redir->out_fd == -1)
		{
			perror("TODO: FREE EVERYTHING Error while opening file");
			return (-1);
		}
		redir->out_filename = get_first_redirection_filename(line, \
														&redir->out_redir_type);
		if (redir->out_filename)
			close(redir->out_fd);
	}
	if (redir->out_fd != -1)
		return (0);
	return (1);
}*/
static int	fill_struct_and_create_files(char *filename, int redir_type, \
												t_redirection *redir)
{
	int	fd;

	if (redir_type == SINGLE_RIGHT_REDIRECT \
	|| redir_type == DOUBLE_RIGHT_REDIRECT)
	{
		redir->out_filename = filename;
		redir->out_redir_type = redir_type;
		fd = open_file_for_redirection(filename, redir_type);
		if (fd == -1)
		{
			perror("TODO: FREE EVERYTHING Error while opening file");
			return (-1);
		}
		close(fd);
	}
	else if (redir_type == SINGLE_LEFT_REDIRECT \
	|| redir_type == DOUBLE_LEFT_REDIRECT)
	{
		redir->in_filename = filename;
		redir->in_redir_type = redir_type;
	}
	return (0);
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
		0 = Success (either no filename found or well parsed)

	If we have another filename, free the previous one, this only keeps
		the last one malloced
*/
int	parse_redirs_and_create_files(char **line, t_redirection *redir)
{
	char	*filename;
	char	*prev_filename;
	int		redir_type;
	int		fd;

	init_redirection_struct(redir);
	filename = get_first_redirection_filename(line, &redir_type);
	while (filename)
	{
		filename = interpret_env_args(filename);
		interpret_quotes(&filename);
		if (fill_struct_and_create_files(filename, redir_type, redir) == -1)
			return (-1);
		prev_filename = filename;
		filename = get_first_redirection_filename(line, &redir_type);
		if (filename)
			ft_free(prev_filename);
	}
	return (0);
}
