/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:50:33 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/11 11:59:04 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL_PROMPT "minishell: "
# define PATH_STR "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./builtins/environment/environment.h"
# include "cmd_list.h"

char	**parse_program_and_args(char *line);
int		is_line_empty(char *str);
t_cmd	*parse_cmds(char *line);

int		execute_program(int input_fd, char *program_path, char **args);
void	execute_builtin(char **args);
int		is_builtin(char *program);
char	*is_program_in_path(char *program);
int		execute_cmd_lst(t_cmd *cmd_lst);

void	unset_command(char *argv[]);
void	env_command(void);
void	export_command(char *argv[]);
void	pwd_cmd(void);
void	cd_cmd(char *argv[]);

#endif