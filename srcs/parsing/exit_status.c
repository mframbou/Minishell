/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 24-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 16:57 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Remove the "$?" from the string and replace it with the exit code
	insert_str_in_str automatically frees
*/
char	*insert_last_exit_status(char *str, int *index)
{
	char	*res;
	char	*exit_status;

	remove_substr_from_string(&str, *index, *index + 2);
	exit_status = ft_itoa(*get_exit_status());
	res = insert_str_in_str(str, exit_status, *index);
	return (res);
}
