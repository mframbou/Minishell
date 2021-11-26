/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:17:24 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/26 11:18:26 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collection.h"

t_ptr_link	**get_ptr_list(void)
{
	static t_ptr_link	*lst = {NULL};

	return (&lst);
}

void	add_ptr_link(void *ptr)
{
	t_ptr_link	**ptr_lst;
	t_ptr_link	*new;
	t_ptr_link	*curr;

	new = (t_ptr_link *) malloc(sizeof(t_ptr_link));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = NULL;
	ptr_lst = get_ptr_list();
	curr = *ptr_lst;
	if (!ptr_lst || !*ptr_lst)
		*ptr_lst = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	ft_free_all(void)
{
	t_ptr_link	**ptr_lst;
	t_ptr_link	*curr;
	t_ptr_link	*prev;

	ptr_lst = get_ptr_list();
	curr = ptr_lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free(prev->ptr);
		free(prev);
	}
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res)
		add_ptr_link(res);
	return (res);
}
