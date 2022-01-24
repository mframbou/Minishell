/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 24-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:28 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_ft_pointer
{
	struct s_ft_pointer		*next;
	void					*ptr;
}	t_ft_pointer;

static t_ft_pointer	**get_ft_malloc_lst(void);

void	ft_free(void *ptr)
{
	t_ft_pointer	**ptr_lst;
	t_ft_pointer	*curr;
	t_ft_pointer	*prev;

	ptr_lst = get_ft_malloc_lst();
	prev = NULL;
	curr = *ptr_lst;
	while (curr && curr != ptr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == ptr)
	{
		if (!prev)
			*ptr_lst = curr->next;
		else
			prev->next = curr->next;
		free(curr->ptr);
		free(curr);
	}
}

void	ft_free_all(void)
{
	t_ft_pointer	**ptr_lst;
	t_ft_pointer	*curr;
	t_ft_pointer	*prev;

	ptr_lst = get_ft_malloc_lst();
	prev = NULL;
	curr = *ptr_lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free(prev->ptr);
		free(prev);
	}
}
