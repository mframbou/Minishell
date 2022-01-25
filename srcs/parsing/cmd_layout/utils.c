/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 25-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 17:20 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	operator = Value in the cmd_layout (e_interpreted_char)
*/
int	is_redirection_operator(int operator)
{
	return (operator == SINGLE_LEFT_REDIRECT \
	|| operator == SINGLE_RIGHT_REDIRECT \
	|| operator == DOUBLE_LEFT_REDIRECT \
	|| operator == DOUBLE_RIGHT_REDIRECT);
}
