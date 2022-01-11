/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_bash_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:59:51 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/11 11:59:51 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Bash variable names consist only of letters, digits or underscore,
	and cannot start with a digit

	- Check if first character is a digit
	- If all other are either digits, alpha or '_', it's fine.
*/
int	is_valid_variable_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || \
						ft_isdigit(str[i])))
		i++;
	if (str[i])
		return (0);
	return (1);
}
