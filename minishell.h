/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:50:33 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 18:01:59 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL_PROMPT "minishell:"

# include <stdlib.h>
# include <stdio.h>
//# include <editline.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./builtins/environment/environment.h"

char	**parse_program_and_args(char *line);
int		execute_command(char **args);
int		does_program_exists(char *program);
int		is_line_empty(char *str);

void	exec_forked_command(char **args);
void	exec_non_forked_command(char **args);
int		is_forked_command(char *program);
int		is_non_forked_command(char *program);

void	unset_command(char *argv[]);
void	env_command(void);
void	export_command(char *argv[]);
void	pwd_cmd(void);
void	cd_cmd(char *argv[]);

#endif