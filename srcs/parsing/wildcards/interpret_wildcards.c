/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 18-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 18-01-2022 22:08 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_one_line_wildcard(void);

/*
	Takes pointer to line ("echo * > test.txt")
	- Interpret wildcard : "echo foo.bar pouet.txt oronda.bg > test.txt"

	If we find a quote skip it, otherwise if we find a * interpret it

	If we have multiple wildcards next to each other, only count 1
	eg. "echo *********" == "echo *"
*/
void	interpret_wildcards(char **line)
{
	int		i;
	char	**files;
	int		wildcard_start;
	int		wildcard_end;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += is_closed_quote(&((*line)[i]));
		if ((*line)[i] == '*')
		{
			wildcard_start = i;
			while ((*line)[i] == '*')
				i++;
			wildcard_end = i;
			remove_substr_from_string(line, wildcard_start, wildcard_end);
			*line = insert_str_in_str(*line, get_one_line_wildcard(), wildcard_start);
			continue ;
		}
		i++;
	}
}
