/* ************************************************************************** */
/*                                                                           */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created:   by            `-'                        `-'                  */
/*   Updated:   by                                                            */
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
char	**parse_program_and_args(char *line);
int		is_line_empty(char *str);
t_cmd	*parse_cmds(char *line);

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