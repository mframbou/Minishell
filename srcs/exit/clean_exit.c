/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 20-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 18:21 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);

void	free_all_and_exit(int code, int current_fd)
{
	return ;
}

void	flush_pipe(int fd)
{
	char	buf[128];
	int		read_val;

	if (fd == -1)
		return ;
	read_val = read(fd, buf, 128);
	while (read_val > 0)
	{
		write(STDOUT_FILENO, buf, read_val);
		read_val = read(fd, buf, 128);
	}
	close(fd);
}
