/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:50:39 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/12 23:42:33 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
# define CMD_LIST_H

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**args;
}	t_cmd;

enum	e_redirection_type
{
	REDIRECT_PIPE,
	REDIRECT_OUTPUT,
	REDIRECT_INPUT,
	REDIRECT_INPUT_DELIMITER,
	REDIRECT_OUTPUT_APPEND
};

void	add_cmd(char **args);
void	clear_cmd_list(void);

#endif
