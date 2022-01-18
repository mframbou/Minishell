/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 18-01-2022 22:10 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
char	**split_command_operands(char *line)
{
	t_cmd_layout	layout;
	int				i;
	int				cmd_start;
	int				cmd_end;
	char			**programs_list;

	create_cmd_layout(&layout, line);
	i = 0;
	cmd_start = 0;
	cmd_end = get_next_non_redirect_operator_index(line, 0);
	programs_list = malloc(sizeof(char *) * \
	(layout.non_redirect_operators_nb + 2));
	while (layout.non_redirect_operators_nb-- >= 0)
	{
		programs_list[i++] = ft_substr(line, cmd_start, cmd_end - cmd_start);
		if (line[cmd_end])
			cmd_end += get_operator_str_len(layout.operator_chars[cmd_end]);
		cmd_start += cmd_end;
		cmd_end = get_next_non_redirect_operator_index(line, cmd_end);
	}
	programs_list[i] = NULL;
	return (programs_list);
}

/*
	Takes our line return a list of fully parsed programs

	when interpreting args, put "" aronud the value for easier parsing
*/
t_cmd	*parse_cmds(char *line)
{
	char			**cmds;
	t_redirection	redirection;
	int				i;

	i = 0;
	cmds = split_command_operands(line);
	// TODO: Interpret wildcards
	while (cmds[i])
	{
		interpret_wildcards(&(cmds[i]));
		if (parse_redirectoins_and_create_files(&(cmds[i]), &redirection) == -1)
		{
			// TODO: Error happened, otherwise we have a correct redirection
			return (NULL);
		}
		//printf("Redirection types:\n> = %d\n >> = %d\n< = %d\n<< = %d\n\n", SINGLE_RIGHT_REDIRECT, DOUBLE_RIGHT_REDIRECT, SINGLE_LEFT_REDIRECT, DOUBLE_LEFT_REDIRECT);
		//printf("Found redirection type in: %d\n", redirection.type);
		//if (redirection.out_fd >= 0)
		//	write(redirection.out_fd, "Salut pouet", 12);
		// Need to add command with correct redirection type, redirection fd and args
		// parse_program_and_args for args, redirect_fd for fd, need a function for redirection type
		add_cmd(parse_program_and_args(cmds[i]), redirection);
		i++;
	}
	//interpret_all_args(&args); // Puts quotes around every arg, must remove it after parsing redirection
	//return(0);
	//for (int i = 0; args[i]; i++)
	//{
	//	printf("arg=\"%s\"\n", args[i]);
	//}
	//printf("\n");
	return (*get_cmd_lst());
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
