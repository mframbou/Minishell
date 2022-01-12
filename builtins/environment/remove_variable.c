/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 2022/01/13 00:41:15 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

static void	lst_remove_env_variable(t_env_link	**var_lst, t_env_link *var)
{
	t_env_link	*curr;

	if (!var_lst || !*var_lst || !var)
		return ;
	if (*var_lst == var)
		*var_lst = (*var_lst)->next;
	else
	{
		curr = *var_lst;
		while (curr && curr->next && curr->next != var)
			curr = curr->next;
		if (curr && curr->next && curr->next == var)
			curr->next = var->next;
	}
	if (var->var.value)
	{
		free(var->var.value);
	}
	free(var->var.key);
	free(var);
}

void	remove_env_variable(char *key)
{
	t_env_link	**var_lst;
	t_env_link	*curr;

	var_lst = get_var_list();
	curr = *var_lst;
	while (curr)
	{
		if (strcmp(curr->var.key, key) == 0)
		{
			lst_remove_env_variable(var_lst, curr);
			return ;
		}
		curr = curr->next;
	}
}
