/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 20-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 20-01-2022 16:17 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);

void free_all_and_exit(int code, int current_fd)
{
	
}

void	free_redirections(void)
{
	t_cmd	*cmds;

	cmds = *get_cmd_lst();
	while (cmds)
	{
		free(cmds->redirection.in_filename);
		free(cmds->redirection.out_filename);
		cmds = cmds->next;
	}
}

void	flush_pipe(int fd)
{
	char	buf;
	int		read_val;

	if (fd == -1)
		return ;
	read_val = read(fd, &buf, 1);
	while (read_val)
	{
		write(STDOUT_FILENO, &buf, 1);
		read_val = read(fd, &buf, 1);
	}
	close(fd);
}
