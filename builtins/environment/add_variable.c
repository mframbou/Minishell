/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:18:25 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/18 15:09:10 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_link	**get_var_list(void);

static t_env_link	*create_new_env_variable(char *key, char **values)
{
	t_env_link	*new;

	new = (t_env_link *) malloc(sizeof(t_env_link));
	if (new)
	{
		new->next = NULL;
		new->var.key = key;
		new->var.values = values;
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

static void	overwrite_var_values(t_env_link *var, char **new_values)
{
	int	i;

	i = 0;
	if (var->var.values)
	{
		while (var->var.values[i])
			free(var->var.values[i++]);
		free(var->var.values);
	}
	free(var->var.key);
	free(var);
}

void	add_env_variable(char *key, char **values)
{
	t_env_link	**var_lst;
	t_env_link	*curr;

	var_lst = get_var_list();
	curr = *var_lst;
	while (curr)
	{
		if (ft_strcmp(curr->var.key, key) == 0)
		{
			overwrite_var_values(curr, values);
			return ;
		}
		curr = curr->next;
	}
	lst_add_env_variable(var_lst, create_new_env_variable(key, values));
}
