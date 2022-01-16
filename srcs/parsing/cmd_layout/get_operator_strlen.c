/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 16-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 16-01-2022 20:49 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_operator_str_len(int operator)
{
	if (operator == PIPE_CHAR || operator == SINGLE_LEFT_REDIRECT || \
	operator == SINGLE_RIGHT_REDIRECT)
		return (1);
	else if (operator == DOUBLE_LEFT_REDIRECT || \
	operator == DOUBLE_RIGHT_REDIRECT || \
	operator == AND_CHAR || operator == OR_CHAR)
		return (2);
	return (0);
}
