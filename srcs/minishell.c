/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 20-01-2022 01:04 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>


#define _GNU_SOURCE // linux

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
		add_env_variable(ft_strdup("HOME"), ft_strdup(home_env));
	else
		add_env_variable(ft_strdup("HOME"), ft_strdup("/"));
	if (path_env)
		add_env_variable(ft_strdup("PATH"), ft_strdup(path_env));
	else
		add_env_variable(ft_strdup("PATH"), ft_strdup(PATH_STR));
}

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &g_termios_save);
}

int	*get_exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

int	set_exit_status(int status)
{
	*get_exit_status() = status;
}

/*
	Move to a new line
	Regenerate prompt on newline
	Clear previous text
	redisplay
*/
void	handle_sigs(int sig/*, siginfo_t *siginfo, void *context*/)
{
	if (sig == SIGINT)
	{
		fprintf(stdout, "Sigint on pid: %d\n", g_pid);
		if (g_pid)
		{
			//printf("pid = %d\n", g_pid);
			printf("\n");
			kill(g_pid, SIGINT);
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
	{
		printf("Sigquit\n");
		if (g_pid)
		{
			kill(g_pid, SIGQUIT);
		}
		return ;
		//printf("Clean exit TODO ctrl \\\n");
		//exit(0);
	}
}

void	init_signals(void)
{
	// int					tmp;
	// struct termios		termios_new;
	// struct sigaction	sa;

	// tmp = tcgetattr(0, &g_termios_save);
	// if (tmp)
	// {
	// 	perror("tcgetattr");
	// 	exit(1);
	// }
	// tmp = atexit(reset_the_terminal);
	// if (tmp)
	// {
	// 	perror("atexit");
	// 	exit(1);
	// }
	// termios_new = g_termios_save;
	// termios_new.c_lflag &= ~ECHOCTL;
	// tmp = tcsetattr(0, 0, &termios_new);
	// if (tmp)
	// {
	// 	perror("tcsetattr");
	// 	exit(1);
	// }
	// sa.sa_sigaction = handle_sigs;
	// sa.sa_flags = 0;
	// sigaction(SIGINT, &sa, 0);
	// sigaction(SIGQUIT, &sa, 0);

	signal(SIGINT, &handle_sigs);
	signal(SIGQUIT, &handle_sigs); // TODO TEST IF IT WORKS
}




/*
	Au final tous les double quotes sont supprimés sauf si ils sont dans des simples quotes
*/
int	main()
{
	char	*line;
	t_cmd	*cmd_list;

	// TODO IMPORTANT Redirect STDOUT but also STDERR
	// todo if we have time, interpret env args before splittigs cmds args (on single line)
	// so that TEST=cho pouet then e$TEST would work but need to keep quotes so it's annoying with eg TEST='cho pouet' which should result in e cho pouet and not echo pouet since its single quotes
	
	init_signals();
	init_basic_env_variables();


	*get_exit_status() = 0; // init exit status to 0
	//add_env_variable(ft_strdup("TEST"), ft_strdup(">"));	

	//line = ft_strdup("echo pouet > \"test 1\".txt \"(should create a file named test 1.txt)\"");
	while (1)
	{
		line = readline(MINISHELL_PROMPT);
		if (line && line[0] != '\0' && !is_line_empty(line))
		{
			add_history(line);

			cmd_list = parse_cmds(line);
			/*t_cmd *curr = cmd_list;
			while (curr)
			{
				curr = curr->next;
			}*/
			if (cmd_list)
				execute_cmd_lst(cmd_list);
			clear_cmd_list();
		}
		else if (line == NULL)
		{
			printf("exit TODO\n");
			exit (1);
		}
	}
}
