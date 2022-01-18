/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:50:39 by mframbou          #+#    #+#             */
/*   Updated: 15-01-2022 18:31 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
	t_redirection	redirection;
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

void	add_cmd(char **args, t_redirection redirection);
void	clear_cmd_list(void);

#endif
