/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 17-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 17-01-2022 18:39 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Opens the file according to the redirection type and returns the fd
*/
int	open_file_for_redirection(char *filename, int redirection_type)
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
	fd = open(filename, flags, mode);
	if (fd == -1)
		perror(filename); // TODO add prompt etc
	return (fd);
}
