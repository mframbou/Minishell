/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:36 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
	//free(*(get_var_list()));
}

void	free_environment(void)
{
	t_env_link	*prev;
	t_env_link	*curr;
	
	curr = *get_var_list();
	while(curr)
	{
		prev = curr;
		curr = curr->next;
		//free(prev->var.key);
		//free(prev->var.value);
		//free(prev);
	}
}
