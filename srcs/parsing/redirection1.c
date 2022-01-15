/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 15-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 15-01-2022 20:59 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
	Opens the file according to the redirection type and returns the fd
*/
static int	open_file_for_redirection(char *filename, int redirection_type)
{
	int	fd;
	int	flags;
	int	mode;

	mode = 0;
	if (redirection_type == SINGLE_LEFT_REDIRECT || redirection_type == DOUBLE_LEFT_REDIRECT)
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

/*
	Takes pointer to program line (eg. "echo 'pouet $HOME' > test.txt") and:
	- extract redirections (new line = "echo 'pouet $HOME'")
		put in the redirection structure in argument
		(fd (x), filename ("test.txt") and type('>'))
	
	Return value:
		-1 = Error
		0 = Success
		1 = No filename found (no redirections in program)
*/
int	get_redirection_and_create_files(char **line, t_redirection *redirection)
{
	char	*filename;
	int		fd;
	int		redir_type;

	redir_type = 0;
	filename = get_first_redirection_filename(line, &redir_type);
	fd = -1;
	redirection->fd = -1;
	redirection->filename = NULL;
	redirection->type = -1;
	while (filename)
	{
		printf("filename = %s\n", filename);
		filename = interpret_env_args(filename);
		interpret_quotes(&filename);
		
		fd = open_file_for_redirection(filename, redir_type);
		if (fd == -1)
		{
			// TODO free everything
			perror("Error while opening file");
			return(-1);
		};
		redirection->filename = filename;
		redirection->fd = fd;
		redirection->type = redir_type;
		filename = get_first_redirection_filename(line, &redir_type);
		if (filename) // If we have another file, else keep the fd opened
			close(fd);
	}
	if (fd != -1);
		return (0);
	return (1);
}

