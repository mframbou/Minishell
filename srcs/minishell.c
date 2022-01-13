/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 13-01-2022 21:21 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

struct termios termios_save;

char	**parse_program_and_args(char *line);
//void	rl_replace_line(char*, int);

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

void reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save );
}

void handle_sigs(int sig, siginfo_t *siginfo, void *context)
{
	if(sig == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		//rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
	if(sig == SIGQUIT)
	{
		printf("Clean exit TODO ctrl \\\n");
		exit(0);
	}
		
}

void init_signals()
{
	int tmp;
	struct termios termios_new;
	

	tmp = tcgetattr(0, &termios_save );
	if (tmp) {
		perror("tcgetattr"); 
		exit(1); 
	}

	tmp = atexit(reset_the_terminal);
	if (tmp) {
		perror("atexit"); 
		exit(1); 
	}

	termios_new = termios_save;
	

	termios_new.c_lflag &= ~ECHOCTL; // Removes flag
	
	tmp = tcsetattr(0, 0, &termios_new );
	if (tmp) {
		perror("tcsetattr");
		exit(1);
	}

	struct sigaction sa;
	sa.sa_sigaction = handle_sigs;	
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}


int	main()
{
	char	*line;
	
	init_signals();
	init_basic_env_variables();
	//line = strdup("ls || grep poeut | wc -l ");
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
			clear_cmd_list();
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
