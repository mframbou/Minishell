/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 16-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 16-01-2022 20:12 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	layout_pipe(t_cmd_layout *layout, char *line, int *index)
{
	if (line[(*index) + 1] && line[(*index) + 1] == '|')
	{
		layout->operator_chars[(*index)] = OR_CHAR;
		layout->operators_nb++;
		layout->non_redirect_operators_nb++;
		((*index))++;
	}
	else
	{
		layout->operator_chars[(*index)] = PIPE_CHAR;
		layout->operators_nb++;
		layout->non_redirect_operators_nb++;
	}
}

static void	layout_right_redirect(t_cmd_layout *layout, char *line, int *index)
{
	if (line[(*index) + 1] && line[(*index) + 1] == '>')
	{
		layout->operator_chars[(*index)] = DOUBLE_RIGHT_REDIRECT;
		layout->operators_nb++;
		(*index)++;
	}
	else
	{
		layout->operator_chars[(*index)] = SINGLE_RIGHT_REDIRECT;
		layout->operators_nb++;
	}
}

static void	layout_left_redirect(t_cmd_layout *layout, char *line, int *index)
{
	if (line[(*index) + 1] && line[(*index) + 1] == '<')
	{
		layout->operator_chars[(*index)] = DOUBLE_LEFT_REDIRECT;
		layout->operators_nb++;
		(*index)++;
	}
	else
	{
		layout->operator_chars[(*index)] = SINGLE_LEFT_REDIRECT;
		layout->operators_nb++;
	}
}

static void	layout_and(t_cmd_layout *layout, char *line, int *index)
{
	if (line[(*index) + 1] && line[(*index) + 1] == '&')
	{
		layout->operator_chars[(*index)] = AND_CHAR;
		(*index)++;
		layout->operators_nb++;
		layout->non_redirect_operators_nb++;
	}
}

/*
	Generates the command layout (find operators like pipe, redirect etc.)
		If we find a quote, don't include the content of the quotes 
		in the layout, we give the address of the index because if we have for
		instance >>, we want to make i one more than if we had >
		(i += 2 instead of i++), functions called do that automatically
*/
void	create_cmd_layout(t_cmd_layout *layout, char *line)
{
	int	i;

	layout->non_redirect_operators_nb = 0;
	layout->operators_nb = 0;
	ft_bzero(layout->operator_chars, 4096);
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && is_closed_quote(&line[i]))
			i += is_closed_quote(&line[i]) + 1;
		if (!line[i])
			break ;
		if (line[i] == '|')
			layout_pipe(layout, line, &i);
		else if (line[i] == '>')
			layout_right_redirect(layout, line, &i);
		else if (line[i] == '<')
			layout_left_redirect(layout, line, &i);
		else if (line[i] == '&')
			layout_and(layout, line, &i);
		i++;
	}
}
