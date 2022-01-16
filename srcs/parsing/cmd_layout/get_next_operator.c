/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 16-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 16-01-2022 21:06 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	operator = Value in the cmd_layout (e_interpreted_char)
*/
static int	is_redirection_operator(int operator)
{
	return (operator == SINGLE_LEFT_REDIRECT \
	|| operator == SINGLE_RIGHT_REDIRECT \
	|| operator == DOUBLE_LEFT_REDIRECT \
	|| operator == DOUBLE_RIGHT_REDIRECT);
}

static int	is_not_redirection_operator(int	operator)
{
	return (operator == PIPE_CHAR \
	|| operator == OR_CHAR \
	|| operator == AND_CHAR);
}

int	get_next_non_redirect_operator_index(char *line, int current_index)
{
	t_cmd_layout	layout;

	create_cmd_layout(&layout, line);
	while (line[current_index] \
	&& !is_not_redirection_operator(layout.operator_chars[current_index]))
		current_index++;
	return (current_index);
}

/*
	Returns the index of the next redirection (<, <<, >, >>) operator
*/
int	get_next_redirect_operator_index(char *line, int current_index)
{
	t_cmd_layout	layout;

	create_cmd_layout(&layout, line);
	while (line[current_index] \
	&& !is_redirection_operator(layout.operator_chars[current_index]))
		current_index++;
	return (current_index);
}

/*
	Returns the type of the next redirection (<, <<, >, >>) operator
*/
int	get_next_redirect_operator_type(char *line, int current_index)
{
	t_cmd_layout	layout;
	int				operator_index;

	create_cmd_layout(&layout, line);
	operator_index = get_next_redirect_operator_index(line, current_index);
	return (layout.operator_chars[operator_index]);
}
