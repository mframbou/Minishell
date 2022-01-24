/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 19:59 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);

/*
	Takes our line (eg. echo "test" > test.txt | cat)
                                    ^          ^
				cmd layout =>  RIGHT_REDIR    PIPE

	Returns a list of commands (just separated on |, || and &&)
	(in this case ["echo "test > test.txt", "cat")

	malloc nb + 2 because if we have 1 operator it means 2 commands, +1 for NULL
	Just check if we found a next operator (if(line[cmd_end])),
		if we do, skip the current operator ('>', '>>', '|' etc.) 
		and go to the next command

	We need to check if the parenthesis are surrounded by operators
	So that we don't have like echo (cat)
	but only cases like echo | (cat), (echo) | cat, and (echo), all other
	are considered invalid
*/
static t_splitted_cmd	*split_command_operands(char *line)
{
	t_cmd_layout	layout;
	int				i;
	int				cmd_start;
	int				cmd_end;
	t_splitted_cmd	*programs_list;

	create_cmd_layout(&layout, line);
	i = 0;
	cmd_start = 0;
	cmd_end = get_next_non_redirect_operator_index(line, 0);
	programs_list = ft_malloc(sizeof(t_splitted_cmd) * \
	(layout.non_redirect_operators_nb + 2));
	while (layout.non_redirect_operators_nb-- >= 0)
	{
		programs_list[i].cmd = ft_substr(line, cmd_start, cmd_end - cmd_start);
		programs_list[i].next_cmd_operator = layout.operator_chars[cmd_end];
		i++;
		if (line[cmd_end])
			cmd_end += get_operator_str_len(layout.operator_chars[cmd_end]);
		cmd_start = cmd_end;
		cmd_end = get_next_non_redirect_operator_index(line, cmd_end);
	}
	programs_list[i].cmd = NULL;
	programs_list[i].next_cmd_operator = 0;
	return (programs_list);
}

/*
	Check if arg is fully in parentheses like (echo test)
	and not (echo test) cat

	if it is not, it's considered invalid

	if ( is not the first char or ) is not the last, it's invalid
*/
int	is_arg_fully_in_parentheses(char *str)
{
	int	i;

	i = 0;
	if (has_parentheses_to_interpret(str))
	{
		if (str[0] != '(')
			return (0);
		else
		{
			i += is_closed_parenthesis(str);
			if (str[i + 1])
				return (0);
		}
	}
	return (1);
}

static char	*parse_parentheses_if_valid(char *cmd)
{
	char	*parentheses_string;

	parentheses_string = NULL;
	if (has_parentheses_to_interpret(cmd))
	{
		if (!is_arg_fully_in_parentheses(cmd))
		{
			printf("Syntax error on argument '%s' : command between parentheses \
			should not contain arguments outside parentheses\n", cmd);
			return (NULL);
		}
		else
			parentheses_string = remove_outer_parentheses(cmd);
	}
	return (parentheses_string);
}

/*
	Takes pointer to list and pointer to current cmd
*/
static int	parse_one_cmd(t_cmd **list, t_splitted_cmd *current_cmd)
{
	t_redirection	redirection;
	char			*parentheses_string;

	parentheses_string = NULL;
	parentheses_string = parse_parentheses_if_valid(current_cmd->cmd);
	if (!parentheses_string)
	{
		interpret_wildcards(&current_cmd->cmd);
		if (parse_redirections_and_create_files(&current_cmd->cmd, &redirection) \
		== -1)
			return (-1);
		add_cmd(list, parse_program_and_args(current_cmd->cmd), redirection, NULL, \
				current_cmd->next_cmd_operator);
	}
	else
	{
		redirection.in_filename = NULL;
		redirection.out_filename = NULL;
		redirection.in_filename = 0;
		redirection.out_filename = 0;
		ft_free(current_cmd->cmd);
		add_cmd(list, NULL, redirection, parentheses_string, \
				current_cmd->next_cmd_operator);
	}
	return (0);
}

/*
	Takes our line return a list of fully parsed programs

	on error, don't free since beginning but only from current index because
		previous ones have already been freed
	- If the arg is between parentheses, keep it as raw line (just remove
		parentheses chars)

	free cmd array at the end (not content since it's already freed in parsing)
*/
t_cmd	*parse_cmds(char *line)
{
	t_splitted_cmd	*cmds;
	t_redirection	redirection;
	t_cmd			*lst;
	int				i;
	char			*tmp;

	i = 0;
	cmds = split_command_operands(line);
	lst = NULL;
	while (cmds[i].cmd)
	{
		tmp = ft_strtrim(cmds[i].cmd, " \n\t\v\f\t");
		ft_free(cmds[i].cmd);
		cmds[i].cmd = tmp;
		if (parse_one_cmd(&lst, &(cmds[i])))
		{
			while (cmds[i].cmd)
				ft_free(cmds[i++].cmd);
			ft_free(cmds);
			return (NULL);
		}
		i++;
	}
	ft_free(cmds);
	return (lst);
}
