/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:31 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_cmd	**get_cmd_lst(void)
// {
// 	static t_cmd	*cmd_lst = NULL;

// 	return (&cmd_lst);
// }

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

void	init_redirection_struct(t_redirection *redirection)
{
	redirection->out_filename = NULL;
	redirection->in_filename = NULL;
	redirection->out_redir_type = 0;
	redirection->in_redir_type = 0;
}

t_cmd	*create_cmd(char **args, t_redirection redirection, char *parenthesis_content, int next_operator)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	if (new)
	{
		new->args = args;
		new->redirection.out_filename = redirection.out_filename;
		new->redirection.in_filename = redirection.in_filename;
		new->redirection.out_redir_type = redirection.out_redir_type;
		new->redirection.in_redir_type = redirection.in_redir_type;
		new->parentheses_content = parenthesis_content;
		new->next_cmd_operator = next_operator;
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
