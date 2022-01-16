/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 16-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 16-01-2022 19:56 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Takes pointer to line because it modifies it
	"Hello "test"" => Hello test (like real bash)
	"Hello 'test'" => Hello 'test' 

	If double quotes are in simple quotes, keep them

	salut.'"test"'' => salut."test"'

	- If we find quotes and they are closed, just remove the literal quote
		character (" / ') and the closing one
*/
void	interpret_quotes(char **str)
{
	int	i;
	int	end_quote;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			end_quote = is_closed_quote(&((*str)[i]));
			if (end_quote)
			{
				remove_char_from_string(str, i);
				remove_char_from_string(str, i + end_quote - 1);
				i += end_quote - 1;
				continue ;
			}
		}
		i++;
	}
}

void	unquote_all_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		interpret_quotes(&(args[i]));
	}
}
