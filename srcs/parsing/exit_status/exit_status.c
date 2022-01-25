/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 24-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 14:27 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	*get_exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

void	set_exit_status(int status)
{
	*get_exit_status() = status;
}

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
