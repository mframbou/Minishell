/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 25-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 27-01-2022 13:54 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Continue while there is space, then check if we have
	either a command or an operator
*/
static int	has_command_after_index(char *str, int i)
{
	t_cmd_layout	layout;

	create_cmd_layout(&layout, str);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == '&')
		return (0);
	return (1);
}

/*
	No need to check if we have reached the end of the line because
	we know it's not an empty line

	returns the index in the line where the error is found, starting from 1
	(so that 0 is only returned if we have no errors)
	Check for cases like 'echo | |', '| cat' etc.

	- If operator at beginning => wrong
	- If operator at end => wrong
	- If operator with no command after => wrong
*/
int	has_syntax_error(char *line)
{
	t_cmd_layout	layout;
	int				i;

	create_cmd_layout(&layout, line);
	i = 0;
	while (line[i] && ft_isspace(line[i]) && !layout.operator_chars[i])
		i++;
	if (layout.operator_chars[i] && \
	!is_redirection_operator(layout.operator_chars[i]) && \
	layout.operator_chars[i] != WILDCARD_CHAR)
		return (i + 1);
	i = -1;
	while (line[++i])
	{
		if (layout.operator_chars[i] && \
		layout.operator_chars[i] != WILDCARD_CHAR)
		{
			if (!line[i + 1] || !has_command_after_index(line, \
			i + get_operator_str_len(layout.operator_chars[i])))
				return (i + 1);
		}
	}
	return (0);
}
