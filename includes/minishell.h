/* ************************************************************************** */
/*                                                                           */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created:   by            `-'                        `-'                  */
/*   Updated: 27-01-2022 13:53 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL_PROMPT "🤡: "
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
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>

// Local
# include "cmd_list.h"
# include "libft.h"
# include "builtins.h"
# include "ft_malloc.h"
# include "readline_extras.h"

int		g_pid;

// Parsing
t_cmd	*parse_cmds(char *line);
char	**parse_program_and_args(char *line);
char	*get_one_arg(char *str, int *i);
char	*interpret_env_args(char *str);
void	interpret_all_args(char	***args);
void	interpret_quotes(char **str);
int		parse_and_execute_line(int input_read_fd, char *line);

// Parsing redirections
char	**remove_empty_args(char **args);
void	unquote_all_args(char **args);
int		perror_return(char *str);
int		parse_redirs_and_create_files(char **line, \
											t_redirection *redirection);
int		get_next_redirect_operator_index(char *line, int current_index);
int		get_next_redirect_operator_type(char *line, int current_index);
int		get_next_non_redirect_operator_index(char *line, int current_index);
int		get_operator_str_len(int operator);
void	init_redirection_struct(t_redirection *redirection);
int		open_file_for_redirection(char *filename, int redirection_type);

// Parsing utils
int		is_line_empty(char *str);
int		is_closed_quote(char *str);
int		is_closed_parenthesis(char *str);
void	remove_substr_from_string(char **str, int start, int end);
void	remove_char_from_string(char **str, size_t index);
void	interpret_quotes(char **str);
void	unquote_all_args(char **args);
int		is_valid_in_filename(char c);
char	*insert_str_in_str(char *src, char *str, size_t index);
char	*convert_str_array_to_one_line(char **array);
void	sort_string_array(char **array);
int		has_syntax_error(char *line);
int		are_parentheses_invalid(char *line);
int		is_redirection_operator(int operator);
int		has_slash(char *str);

// Exit
int		*get_exit_status(void);
void	set_exit_status(int status);
char	*insert_last_exit_status(char *str, int *index);
int		should_exit(void);
void	set_should_exit(int code);
// Redirections
int		read_until_delimiter(char *delimiter);

// Terminal
void	set_terminal_attributes(int term_type);
enum e_current_terminal
{
	ECHOCTL_ON = 0,
	ECHOCTL_OFF = 1
};

// Execution
char	*search_absolute_path_program(char *program);
int		is_regular_file_or_symlink(char *file);
int		execute_program(int input_fd, char *program_path, char **args);
int		execute_builtin(char **args);
int		is_builtin(char *program);
char	*is_program_in_path(char *program);

typedef struct s_splitted_cmd
{
	char	*cmd;
	int		next_cmd_operator;
}	t_splitted_cmd;

// Clean exit
void	flush_pipe(int fd);
void	clean_exit(int read_fd);

// Layout
typedef struct s_cmd_layout
{
	int	operator_chars[4096];
	int	operators_nb;
	int	non_redirect_operators_nb;
}	t_cmd_layout;
void	create_cmd_layout(t_cmd_layout *layout, char *line);

// Exit status
int		*get_exit_status(void);
void	set_exit_status(int status);
char	*insert_last_exit_status(char *str, int *index);

/*
	|
	>
	>>
	<
	<<
	||
	&&
*/
typedef enum e_interpreted_char
{
	PIPE_CHAR = 1,
	SINGLE_RIGHT_REDIRECT,
	DOUBLE_RIGHT_REDIRECT,
	SINGLE_LEFT_REDIRECT,
	DOUBLE_LEFT_REDIRECT,
	OR_CHAR,
	AND_CHAR,
	WILDCARD_CHAR
}	t_interpreted_char;

// Signals
void	init_signals(void);

// parentheses
char	*remove_outer_parentheses(char *str);
int		has_parentheses_to_interpret(char *str);

// Wildcard
void	interpret_wildcards(char **line);

// Environment
void	add_env_variable(char *key, char *value);
void	remove_env_variable(char *key);
void	free_environment(void);
char	*get_env_variable(char *key);
char	**get_env_as_string_array(void);

#endif