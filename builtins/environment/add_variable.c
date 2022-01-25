/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 25-01-2022 14:05 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

static t_env_link	*create_new_env_variable(char *key, char *value)
{
	t_env_link	*new;

	new = (t_env_link *) malloc(sizeof(t_env_link));
	if (new)
	{
		new->next = NULL;
		new->var.key = key;
		new->var.value = value;
	}
	return (new);
}

static void	lst_add_env_variable(t_env_link **var_lst, t_env_link *new)
{
	t_env_link	*start;

	start = *var_lst;
	if (!start)
	{
		*var_lst = new;
		return ;
	}
	while (start->next)
		start = start->next;
	start->next = new;
}

static void	overwrite_var_value(t_env_link *var, char *new_value)
{
	if (var->var.value)
		ft_free(var->var.value);
	var->var.value = new_value;
}

void	add_env_variable(char *key, char *value)
{
	t_env_link	**var_lst;
	t_env_link	*curr;

	var_lst = get_var_list();
	curr = *var_lst;
	while (curr)
	{
		if (ft_strcmp(curr->var.key, key) == 0)
		{
			overwrite_var_value(curr, value);
			return ;
		}
		curr = curr->next;
	}
	lst_add_env_variable(var_lst, create_new_env_variable(key, value));
}
