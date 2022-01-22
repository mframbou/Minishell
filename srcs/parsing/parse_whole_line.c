/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 22-01-2022 23:51 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
*/
t_splitted_cmd	*split_command_operands(char *line)
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
	programs_list = malloc(sizeof(t_splitted_cmd) * \
	(layout.non_redirect_operators_nb + 2));
	while (layout.non_redirect_operators_nb-- >= 0)
	{
		programs_list[i].cmd = ft_substr(line, cmd_start, cmd_end - cmd_start);
		programs_list[i].next_cmd_operator = layout.operator_chars[cmd_end]; // we already have it
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


int	has_parentheses_to_interpret(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += is_closed_quote(&(str[i]));
		else if (str[i] == '(' && is_closed_parenthesis(&str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
	Check if arg is fully in parentheses like (echo test)
	and not (echo test) cat

	if it is not, it's considered invalid
*/
int is_arg_only_in_parentheses(char *str)
{
	int	i;

	i = 0;
	if (has_parentheses_to_interpret(str))
	{
		if (str[0] != '(') // If we have parenthesis but first char is not one, it's automatically invalid
			return (0);
		else
		{
			i += is_closed_parenthesis(str);
			if (str[i + 1]) // If the closing parenthesis is not the last char, it's also invalid
				return (0);
		}
	}
	return (1); // If the first char is a ( and it is well closed, arg is valid
}

char	*remove_first_parentheses(char *str)
{
	int		i;
	int		first;
	int		second;
	char	*res;

	i = 0;
	res = ft_strdup(str);
	while (res[i])
	{
		if (res[i] == '(' && is_closed_parenthesis(&res[i]))
		{
			first = i;
			second = is_closed_parenthesis(&(res[i])) - 1; // Since we removed one char already
			remove_char_from_string(&res, first);
			remove_char_from_string(&res, second);
			break ;
		}
		i++;
	}
	return (res);
}

/*
	Takes our line return a list of fully parsed programs

	when interpreting args, put "" aronud the value for easier parsing
*/
t_cmd	*parse_cmds(char *line)
{
	t_splitted_cmd	*cmds;
	t_redirection	redirection;
	int				i;
	char			*parentheses_string;
	t_cmd			*lst;

	i = 0;
	cmds = split_command_operands(line);
	/*
		We need to check if the parenthesis are surrounded by operators
		So that we don't have like echo (cat)
		but only cases like echo | (cat), (echo) | cat, and (echo), all other
		are considered invalid
	*/
	lst = NULL;
	while (cmds[i].cmd)
	{
		char *tmp = ft_strtrim(cmds[i].cmd, " \n\t\v\f\t");
		free(cmds[i].cmd);
		cmds[i].cmd = tmp;
		parentheses_string = NULL;

		if (has_parentheses_to_interpret(cmds[i].cmd))
		{
			if (!is_arg_only_in_parentheses(cmds[i].cmd))
			{
				printf("Syntax error on argument '%s' : command between parentheses should not contain arguments outside parentheses\n", cmds[i].cmd);
				// Don't free from beginning but only remaining commands, because previous have already been freed
				//while (cmds[i])
				//	free(cmds[i++]);
				//free(cmds);
				return (NULL);
			}
			else
			{
				parentheses_string = remove_first_parentheses(cmds[i].cmd);
			}
		}

		if (!parentheses_string) // If the cmd is in parentheses, don't do anything just keep raw line
		{
			interpret_wildcards(&(cmds[i].cmd));
			if (parse_redirections_and_create_files(&(cmds[i].cmd), &redirection) == -1)
			{
				// TODO: Error happened, otherwise we have a correct redirection
				return (NULL);
			}
			add_cmd(&lst, parse_program_and_args(cmds[i].cmd), redirection, NULL, cmds[i].next_cmd_operator);
		}
		else
		{
			redirection.in_filename = NULL;
			redirection.out_filename = NULL;
			redirection.in_filename = 0;
			redirection.out_filename = 0;
			free(cmds[i].cmd); // free it since we don't pass it to parsing
			add_cmd(&lst, NULL, redirection, parentheses_string, cmds[i].next_cmd_operator);
		}		
		i++;
	}
	free(cmds); // Strings are already freed in parsing, just need to free array of string
	//free_ft_split(cmds);
	//interpret_all_args(&args); // Puts quotes around every arg, must remove it after parsing redirection
	//return(0);
	//for (int i = 0; args[i]; i++)
	//{
	//	printf("arg=\"%s\"\n", args[i]);
	//}
	//printf("\n");
	return (lst);
}
/*
	"echo "$USER" | cat > pouet.txt"

	
	["echo "$USER" (output fd = input of "cat"), "cat > pouet.txt"]
	["echo "mframbou"" | cat > pouet.txt"]
	["echo "mframbou"" (output fd = input of "cat"), "cat" (output fd = "pouet.txt")]
	[["echo", "mframbou" (output fd = input of "cat")], ["cat"]]

	Execute

	- Split programs
	- interpret environment
	- Remove redirections
	- Fully parse program
	- Execute
*/
