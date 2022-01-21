/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 15-01-2022 18:33 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);
t_cmd	*create_cmd(char **args, t_redirection redirection);
void	add_cmd_to_lst(t_cmd **lst, t_cmd *new);

void	add_cmd(char **args, t_redirection redirection)
{
	t_cmd	**cmd_lst;

	cmd_lst = get_cmd_lst();
	add_cmd_to_lst(cmd_lst, create_cmd(args, redirection));
}

void	clear_cmd_list(void)
{
	t_cmd	**cmd_lst;
	t_cmd	*curr;
	t_cmd	*prev;

	cmd_lst = get_cmd_lst();
	curr = *cmd_lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		prev->next = NULL;
		free_ft_split(prev->args);
		free(prev);
	}
	*cmd_lst = NULL;
}