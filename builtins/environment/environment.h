/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:47:39 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/22 15:01:04 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "environment.h"
# include "../builtins.h"

typedef struct s_dic_variable
{
	char	*key;
	char	**values;
}	t_env_variable;

typedef struct s_env_link
{
	t_env_variable		var;
	struct s_env_link	*next;
}	t_env_link;

void	add_env_variable(char *key, char **values);
void	remove_env_variable(char *key);
char	**get_env_variable(char *key);
void	free_var_list(void);

#endif