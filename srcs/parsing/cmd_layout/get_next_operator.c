/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 16-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 25-01-2022 17:29 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_not_redirection_operator(int operator)
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
