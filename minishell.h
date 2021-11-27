/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:50:33 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/27 12:48:34 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <editline.h>
//# include <readline/readline.h>
//# include <readline/history.h>
# include "./builtins/environment/environment.h"

char	**parse_program_and_args(char *line);
int		execute_command(char **args);

#endif