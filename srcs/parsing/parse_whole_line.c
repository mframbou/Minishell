/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 13-01-2022 17:00 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	**get_cmd_lst(void);

// #define PIPE_CHAR 1
// #define OR_CHAR 2;
// #define SINGLE_AMPERSTAND 4; // &&
// #define DOUBLE_AMPERSTAND 4; // &&
// #define AND_CHAR 5;
// #define SINGLE_LEFT_REDIRECT 6;
// #define DOUBLE_LEFT_REDIRECT 7;
// #define SINGLE_RIGHT_REDIRECT 8;
// #define DOUBLE_RIGHT_REDIRECT 9;

typedef struct s_cmd_layout
{
	int splitable_char_pos[4096];
	int splitable_char[4096];
	int nb_of_splitable_chars;
} t_cmd_layout;

typedef enum e_splitable_char
{
	 PIPE_CHAR = 1, 			// |
	 SINGLE_RIGHT_REDIRECT,		// >
	 SINGLE_LEFT_REDIRECT, 		// <
	 OR_CHAR, 					// ||
	 AND_CHAR, 					// &&
	 DOUBLE_LEFT_REDIRECT, 		// <<
	 DOUBLE_RIGHT_REDIRECT 		// >>
}	t_splitable_char;

int is_splitable_char(char c)
{
	if ( c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

void	layout_pipe(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '|' && line[(*index) + 1])
	{
		layout->splitable_char[(*index)] = OR_CHAR;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
		((*index))++;
	}
	else
	{
		layout->splitable_char[(*index)] = PIPE_CHAR;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
	}
}

void	layout_or(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] && line[(*index) + 1] == '|')
	{
		layout->splitable_char[(*index)] = OR_CHAR;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
		((*index))++;
	}
	if (line[(*index) + 1] && line[(*index) + 1] != '|')
	{
		layout->splitable_char[(*index)] = PIPE_CHAR;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
	}
}

void layout_right_redirect(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '>' && line[(*index) + 1])
	{
		layout->splitable_char[(*index)] = DOUBLE_RIGHT_REDIRECT;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
		(*index)++;
	}
	else
	{
		layout->splitable_char[(*index)] = SINGLE_RIGHT_REDIRECT;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
	}
}
void layout_left_redirect(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '<' && line[(*index) + 1])
	{
		layout->splitable_char[(*index)] = DOUBLE_LEFT_REDIRECT;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
		(*index)++;
	}
	else
	{
		layout->splitable_char[(*index)] = SINGLE_LEFT_REDIRECT;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
	}
}
void layout_and(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '&' && line[(*index) + 1])
	{
		layout->splitable_char[(*index)] = AND_CHAR;
		layout->splitable_char_pos[(*index)] = (*index);
		(*index)++;
		layout->nb_of_splitable_chars++;
	}
}

void set_layout_char(t_cmd_layout *layout, char* line, int *index)
{
	if(line[(*index)] == '|')
		layout_pipe(layout,line,index);	
	else if (line[(*index)] == '>')
		layout_right_redirect(layout,line,index);	
	else if (line[(*index)] == '<')
		layout_left_redirect(layout,line,index);	
	else if (line[(*index)] == '&')
		layout_and(layout,line,index);
}

void create_cmd_layout(t_cmd_layout *layout, char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (is_splitable_char(line[i]))
		{
			if(is_splitable_char(line[i]) && line[i])
			{
				set_layout_char(layout, line, &i);
			}
		}
		i++;
	}
}

int	get_redirect_type_associated_with_redirect_char(int redirect_char)
{
	if (redirect_char == PIPE_CHAR)
		return (REDIRECT_PIPE);
	else if (redirect_char == SINGLE_RIGHT_REDIRECT)
		return (REDIRECT_OUTPUT_FILE);
	else if (redirect_char == DOUBLE_RIGHT_REDIRECT)
		return (REDIRECT_OUTPUT_FILE_APPEND);
	else if (redirect_char == SINGLE_LEFT_REDIRECT)
		return (REDIRECT_INPUT_FILE);
	else if (redirect_char == DOUBLE_LEFT_REDIRECT)
		return (REDIRECT_INPUT_FILE_DELIMITER);
	else
		return (REDIRECT_UNKNOWN);
}

int	is_invalid_in_filename(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == ':' || c == '&');
}

char

//"echo >test.txt pouet pouet"

t_cmd	*split_cmds(t_cmd_layout *layout, char *line)
{
	
	int 	i;
	int		cmd_start;
	int		cmd_end;
	char	*program;
	int		redirect_type;

	i = 0;
	cmd_start = 0;
	while (line[i] && !(layout->splitable_char[i] == PIPE_CHAR || layout->splitable_char[i] == OR_CHAR || layout->splitable_char[i] == AND_CHAR))
		i++;
	cmd_end = i;
	//redirect_type = get_redirect_type_associated_with_redirect_char(layout->splitable_char[i]);
	i++;
	while(layout->nb_of_splitable_chars-- >= 0)
	{
		program = ft_substr(line, cmd_start, cmd_end - cmd_start);
		//if (is_line_empty(program))
		//{
		//	printf("%sError ma boi (wrong syntax)\n", MINISHELL_PROMPT);
		//	return (NULL);
		//}

		printf("Program=\"%s\"\n", program);
		//if (layout->nb_of_splitable_chars == -1) // Last program
		//	redirect_type = REDIRECT_STDOUT;
		

		//re_parse(program);
		char **args = parse_program_and_args(program);
		/*
		echo
		>test.txt prout>pouet.txt

		>
		test.txt
		prout
		>
		pouet.txt



		*/

		//add_cmd
		
		int split_char = layout->splitable_char[cmd_end];
		if (split_char == PIPE_CHAR) // |
			cmd_start = cmd_end + 1;
		else // || or &&
			cmd_start = cmd_end + 2;
		while (line[i] && !(layout->splitable_char[i] == PIPE_CHAR || layout->splitable_char[i] == OR_CHAR || layout->splitable_char[i] == AND_CHAR))
			i++;
		cmd_end = i;
		//redirect_type = get_redirect_type_associated_with_redirect_char(layout->splitable_char[i]);
		i++;
	}
	return (*(get_cmd_lst()));
}

t_cmd	*parse_cmds(char *line)
{
	t_cmd	*cmds;
	int		i;
	t_cmd_layout layout;

	layout.nb_of_splitable_chars = 0;
	ft_bzero(layout.splitable_char, 4096);
	ft_bzero(layout.splitable_char_pos, 4096);
	
	create_cmd_layout(&layout, line);
	cmds = split_cmds(&layout, line);
	//cmds = ft_split(line, '|'); // TODO: Better parsing (more error checks, <<, <, > and >> characters)

	i = 0;
	if (!cmds)
		return (NULL);
	/*while (cmds[i])
	{
		add_cmd(parse_program_and_args(cmds[i]));
		i++;
	}*/
	return (cmds);
}


/*
	echo "pouet" | grep pouet > test.txt  || cat 

	&& ||

	|

	< << > >>

	"echo pouet"
	"grep pouet > test.txt > test2.txt salut123 && sjkgdskflgb"
	"sjkgdskflgb"

	echo pouet
	grep pouet
	text.txt
	test2.txt salut123
*/