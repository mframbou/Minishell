/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:50:39 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/11 12:04:18 by mframbou         ###   ########.fr       */
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

void	add_cmd_to_lst(t_cmd **lst, t_cmd *new);
t_cmd	*create_cmd(char **args);
void	clear_cmds(void);

#endif
