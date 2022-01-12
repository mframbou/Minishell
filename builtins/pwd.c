/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created:   by                 `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated:   by                     /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	If the string passed is null, getcwd allocates it with a buffer of size n,
	If n is 0, getcwd automatically malloc the required length
	Returns the address of the buffer (which changed because it was malloc'ed)
*/
void	pwd_command(char *argv[], int output_fd)
{
	char	*curr_path;

	(void) argv;
	curr_path = NULL;
	curr_path = getcwd(curr_path, 0);
	ft_putstr_fd(curr_path, output_fd);
	ft_putchar_fd('\n', output_fd);
	free(curr_path);
}
