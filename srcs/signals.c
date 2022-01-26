/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 26-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 26-01-2022 13:23 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_pid)
	{
		write(STDOUT_FILENO, "\n", 1);
		kill(g_pid, SIGINT);
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_sigquit(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (g_pid == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		kill(g_pid, SIGQUIT);
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		ft_putnbr_fd(sig, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		set_exit_status(sig + 128);
	}
}

/*
	- Move to a new line
	- Regenerate prompt on newline
	- Clear previous text
	- Redisplay
*/
static void	handle_sigs(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGINT)
	{
		handle_sigint(sig);
	}
	else if (sig == SIGQUIT)
	{
		handle_sigquit(sig);
	}
}

/*
	termios_old = termios before
	termios_new = same with ECHOCTL flag removed
*/
void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sigs;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, 0))
		clean_exit(-1);
	if (sigaction(SIGQUIT, &sa, 0))
		clean_exit(-1);
}
