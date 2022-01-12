#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);

t_cmd	*parse_cmds(char *line)
{
	char	**cmds;
	int		i;

	cmds = ft_split(line, '|'); // TODO: Better parsing (more error checks, <<, <, > and >> characters)
	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds[i])
	{
		add_cmd(parse_program_and_args(cmds[i]));
		i++;
	}
	return (*(get_cmd_lst()));
}

