#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void)
{
	static t_cmd *cmd_lst = NULL;

	return (&cmd_lst);
}

static t_cmd	*get_last_cmd(t_cmd *lst)
{
	t_cmd	*prev;

	prev = NULL;
	while (lst)
	{
		prev = lst;
		lst = lst->next;
	}
	return (prev);
}

t_cmd	*create_cmd(char **args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new)
	{
		new->args = args;
		new->next = NULL;
	}
	return (new);
}

void	add_cmd_to_lst(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst)
		return ;
	last = get_last_cmd(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}
