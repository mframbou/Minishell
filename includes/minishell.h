/* ************************************************************************** */
/*                                                                           */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created:   by            `-'                        `-'                  */
/*   Updated: 13-01-2022 21:34 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL_PROMPT "minishell: "
# define PATH_STR "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

// Libs
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

// Local
# include "cmd_list.h"
# include "libft.h"
# include "builtins.h"

// Parsing
t_cmd	*parse_cmds(char *line);
char	**parse_program_and_args(char *line);
char	*get_one_arg(char *str, int *i);
char	*interpret_env_arg(char *str);
void	interpret_all_args(char	***args);

// Parsing redirections
char	**remove_empty_args(char **args);
char	*get_unquoted_arg(char *str);
void	unquote_all_args(char **args);

// Parsing utils
int		is_line_empty(char *str);
int		is_closed_quote(char *str);

// Program execution
int		execute_program(int input_fd, char *program_path, char **args);
int		execute_builtin(char **args);
int		is_builtin(char *program);
char	*is_program_in_path(char *program);
int		execute_cmd_lst(t_cmd *cmd_lst);

// Environment
void	add_env_variable(char *key, char *value);
void	remove_env_variable(char *key);
void	free_var_list(void);
char	*get_env_variable(char *key);
char	**get_env_as_string_array(void);

#endif