/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:45:30 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/11 11:30:31 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_program_and_args(char *line);

int	is_line_empty(char *str)
{
	while (ft_isspace(*str) && *str)
		str++;
	if (*str)
		return (0);
	return (1);
}

void	init_basic_env_variables(void)
{
	char	*home_env;
	char	*path_env;

	home_env = getenv("HOME");
	path_env = getenv("PATH");
	if (home_env)
		add_env_variable("HOME", ft_strdup(home_env));
	else
		add_env_variable("HOME", ft_strdup("/"));
	if (path_env)
		add_env_variable("PATH", ft_strdup(path_env));
	else
		add_env_variable("PATH", ft_strdup(PATH_STR));
}

void handle_sigs(int sig, siginfo_t *siginfo, void *context)
{
	if(sig == SIGINT)
	{
		printf("ctrl + C");
	}
	if(sig == SIGQUIT)
	{
		printf("ctrl + /");
	}
		
}

void init_signals()
{
	struct sigaction sa;
	sa.sa_sigaction = handle_sigs;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa,0);
	sigaction(SIGQUIT, &sa,0);
}


int	main(int argc, char *argv[])
{
	char	*line;

	init_signals();

	init_basic_env_variables();
	while (1) 
	{
		line = readline(MINISHELL_PROMPT);
		if (line && line[0] != '\0' && !is_line_empty(line))
		{
			add_history(line);
		}
		if (line)
		{
			t_cmd *cmd_list = parse_cmds(line);
			if (cmd_list)
				execute_cmd_lst(cmd_list);
			clear_cmds();
		}



		/* This prints parsed cmds, works fine
		t_cmd *curr;
		int j = 0;

		curr = cmd_list;
		while (curr)
		{
			char **args = curr->args;

			printf("Program %d:\n", j++);
			for (int i = 0; args[i]; i++)
			{
				printf("%s\n", args[i]);
			}
			curr = curr->next;
		}
		*/

		
		
		/* old cmd execution
		char **args = parse_program_and_args(line);
		printf("CMD: %s\n", args[0]);
		if (args[0])
		{
			char *program = is_program_in_path(args[0]);
			if (is_builtin(args[0]))
			{
				execute_builtin(args);
			}
			else if (program)
			{
				//printf("Program not builtin but in path\n");
				execute_program(0, program, args);
				free(program);
			}
			else
			{
				printf("%s%s: command not found\n", MINISHELL_PROMPT, args[0]);
			}
		}
		*/
	}
}
