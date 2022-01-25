/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:50:39 by mframbou          #+#    #+#             */
/*   Updated: 22-01-2022 23:52 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
# define CMD_LIST_H

# include "minishell.h"

typedef struct s_redirection
{
	char	*out_filename;
	char	*in_filename;
	int		out_redir_type;
	int		in_redir_type;
}	t_redirection;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**args;
	int				next_cmd_operator;
	t_redirection	redirection;
	char			*parentheses_content; // If there is something between (), just substr the whole content
}	t_cmd;

enum	e_operator
{
	REDIRECT_PIPE,	
	REDIRECT_OUTPUT_FILE,
	REDIRECT_INPUT_FILE,
	REDIRECT_INPUT_FILE_DELIMITER,	
	REDIRECT_OUTPUT_FILE_APPEND,
	REDIRECT_STDOUT,				
	REDIRECT_UNKNOWN
};

void	add_cmd_normal(t_cmd **cmd_lst, char **args, t_redirection redirection, \
						int next_operator);
void	add_cmd_parentheses(t_cmd **cmd_lst, t_redirection redirection, \
							char *parentheses_content, int next_operator);
void	clear_cmd_list(t_cmd **cmd_lst);

#endif
