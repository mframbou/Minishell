/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:17:45 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 18:45:30 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTION_H
# define GARBAGE_COLLECTION_H

#include <stdlib.h>

typedef struct s_ptr_link
{
	void				*ptr;
	struct s_ptr_link	*next;
}	t_ptr_link;

void	*ft_malloc(size_t size);
void	ft_free_all(void);

#endif