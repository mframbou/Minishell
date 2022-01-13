/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 13-01-2022 13:20 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);

t_cmd	*parse_cmds(char *line)
{
	char	**cmds;
	int		i;

	cmds = ft_split(line, '|'); // TODO: Better parsing (more error checks, <<, <, > and >> characters)
	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds[i])
	{
		add_cmd(parse_program_and_args(cmds[i]));
		i++;
	}
	return (*(get_cmd_lst()));
}

