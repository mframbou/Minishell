/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 14-01-2022 17:57 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

struct termios	g_termios_save;

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

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &g_termios_save);
}

void	handle_sigs(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("Clean exit TODO ctrl \\\n");
		exit(0);
	}
}

void	init_signals(void)
{
	int					tmp;
	struct termios		termios_new;
	struct sigaction	sa;

	tmp = tcgetattr(0, &g_termios_save);
	if (tmp)
	{
		perror("tcgetattr");
		exit(1);
	}
	tmp = atexit(reset_the_terminal);
	if (tmp)
	{
		perror("atexit");
		exit(1);
	}
	termios_new = g_termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tmp = tcsetattr(0, 0, &termios_new);
	if (tmp)
	{
		perror("tcsetattr");
		exit(1);
	}
	sa.sa_sigaction = handle_sigs;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}


/*
	Au final tous les double quotes sont supprimés sauf si ils sont dans des simples quotes
*/
int	main()
{
	char	*line;
	t_cmd	*cmd_list;

	init_signals();
	init_basic_env_variables();
	add_env_variable(ft_strdup("TEST"), ft_strdup(">"));
	//line = strdup("echo test > test.txt > pouet.txt> prout.txt>tes2r2rtwe\"oui\".txt");
	while (1)
	{
		line = readline(MINISHELL_PROMPT);
		if (line && line[0] != '\0' && !is_line_empty(line))
		{
			add_history(line);
		}
		if (line)
		{
			cmd_list = parse_cmds(line);
			//if (cmd_list)
			//	execute_cmd_lst(cmd_list);
			//clear_cmd_list();
		}
	}
}
