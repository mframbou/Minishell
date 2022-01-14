/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:50:39 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/13 11:33:02 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
# define CMD_LIST_H

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**args;
	int				redirect_type;
	char			*redirect_filename;
}	t_cmd;

enum	e_redirection_type
{
	REDIRECT_PIPE,   		 		// |
	REDIRECT_OUTPUT_FILE,         	// >
	REDIRECT_INPUT_FILE,  		 	// <
	REDIRECT_INPUT_FILE_DELIMITER,	// <<
	REDIRECT_OUTPUT_FILE_APPEND,   	// >>
	REDIRECT_STDOUT,				// Print output
	REDIRECT_UNKNOWN				// Unknown						
};

void	add_cmd(char **args, int redirection_type);
void	clear_cmd_list(void);

#endif
