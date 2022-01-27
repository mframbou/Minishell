/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 14:33 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void)
{
	static t_env_link	*var_list = NULL;

	return (&var_list);
}

void	free_var_list(void)
{
	ft_free(*(get_var_list()));
}

void	free_environment(void)
{
	t_env_link	*prev;
	t_env_link	*curr;

	curr = *get_var_list();
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		ft_free(prev->var.key);
		ft_free(prev->var.value);
		ft_free(prev);
	}
}
