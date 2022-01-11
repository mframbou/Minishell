/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:50:20 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/11 12:04:20 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd_list.h"

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
