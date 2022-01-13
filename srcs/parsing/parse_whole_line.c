/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 13-01-2022 23:03 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
	int	nb_of_non_redirect_splitable_chars;
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
		layout->nb_of_non_redirect_splitable_chars++;
		((*index))++;
	}
	else
	{
		layout->splitable_char[(*index)] = PIPE_CHAR;
		layout->splitable_char_pos[(*index)] = (*index);
		layout->nb_of_splitable_chars++;
		layout->nb_of_non_redirect_splitable_chars++;
	}
}

// void	layout_or(t_cmd_layout *layout, char *line, int *index)
// {
// 	if(line[(*index) + 1] && line[(*index) + 1] == '|')
// 	{
// 		layout->splitable_char[(*index)] = OR_CHAR;
// 		layout->splitable_char_pos[(*index)] = (*index);
// 		layout->nb_of_splitable_chars++;
// 		layout->nb_of_non_redirect_splitable_chars++;
// 		((*index))++;
// 	}
// 	if (line[(*index) + 1] && line[(*index) + 1] != '|')
// 	{
// 		layout->splitable_char[(*index)] = PIPE_CHAR;
// 		layout->splitable_char_pos[(*index)] = (*index);
// 		layout->nb_of_splitable_chars++;
// 		layout->nb_of_non_redirect_splitable_chars++;
// 	}
// }

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
		layout->nb_of_non_redirect_splitable_chars++;
	}
}

void set_layout_char(t_cmd_layout *layout, char* line, int *index)
{
	if (line[(*index)] == '|')
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

int	is_valid_in_filename(char c)
{
	return (!(c == '>' || c == '<' || c == '|' || c == ':' || c == '&'));
}


//"echo >test.txt pouet pouet"

static int	is_quoted_arg(char *str)
{
	return ((str[0] == '\'' || str[0] == '\"') && is_closed_quote(str));
}
/*
	Args need to NOT be unquoted (">" should stay ">" and not become only >)
	So that we can make difference between literal string (">") 
		and redirect char (>)
	This takes args as input (eg. ["echo", "salut bg", ">", "test.txt"]) and :

	- Remove the redirection from args (new args = ["echo", "salut bg"])
	- Returns the file ("test.txt")
	args[0] = program_name, so skip it

	filename = pointer to first char of filename (string)
	filename_length is the length for the substr'

	i = args index (current arg)
	j = string index (current char)
	k = filename index (current char in filename)

*/
char	*get_first_redirection_file(char **args)
{
	int		i;
	int		j;
	int		k;
	char	*filename;
	int		filename_length;
	int		has_another_redirect;

	char	*final_filename;
	char	*last_filename;

	i = 1;
	has_another_redirect = 0;
	j = 0;
	last_filename = NULL;
	final_filename = NULL;
	while (args[i])
	{
		filename = NULL;
		if (is_quoted_arg(args[i])) // If we have a closed quote, we don't interpret the redirection
		{
			printf("Redirection is in quote, don't interpret\n");
			//return (NULL);
		}
		else
		{
			while (args[i][j] && !(args[i][j] == '<' || args[i][j] == '>')) // While we do not encounter redirect chars, continue
				j++;
			if (args[i][j]) // If a redirection is found
			{
				if (args[i][j + 1] == '>' || args[i][j + 1] == '<') // If we have a double redirection (<< or >>), length is 2 not 1
					j += 2;
				else
					j += 1; // Skip the '>' char
				while (args[i][j] && ft_isspace(args[i][j]))
					j++;
				if (args[i][j]) // We reached a character in the arg (It's either a ">file.txt or >  file.txt" case)
					filename = &(args[i][j]);
				else // Our arg was only composed of a ">", so file is in next arg;
				{
					if (!args[i + 1]) // If there is no next argument, we have an error
					{
						printf("Missing filename. TODO\n");
						return (NULL);
					}
					else
						filename = args[i + 1];
				}
				k = 0; // Now that we have our string filename, start from first char
				while (filename[k] && is_valid_in_filename(filename[k]))
					k++;
				final_filename = ft_substr(filename, 0, k);


				// SHOULD MOVE THIS TO ANOTHER FUNCTION
				/*
				Appended output redirection shall cause the file whose name results from the expansion of word to be opened for output on the designated file descriptor.
				 The file is opened as if the open() function as defined in the System Interfaces volume of POSIX.1-2008 was called with the O_APPEND flag. 
				 If the file does not exist, it shall be created.


				I ran this: strace -o spork.out bash -c "echo 1234 >> some-file" to figure out your question. This is what I found:

				open("some-file", O_WRONLY|O_CREAT|O_APPEND, 0666) = 3
				No file named "some-file" existed in the directory in which I ran the echo command.
				*/
				//int fd = open (final_filename,  O_WRONLY | O_CREAT);
				//close(fd);
				
				if (final_filename)
				{
					free(last_filename);
					last_filename = ft_strdup(final_filename);
					
				}
				final_filename = NULL;
				
				while (filename[k] && !(filename[k] == '>' || filename[k] == '<')) // Check if we have another redirection next
					k++;
				if (filename[k]) // Here we have another redirection next
				{
					// Stay at the same index in the same string and operate once more
					// Preserve the index j for the next iteration
					continue; // Since we continue there is no i++ so we run the loop again but with j != 0 this time (not starting from the beginning of the string)
				}
				else
					j = 0; // Go back at the beginning of the new string
				// If we reached here, we have our filename no matter what case we are in
			}
			else
				j = 0;
		}
		i++;
	}
	printf("last redirect=\"%s\"\n", last_filename);
}


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
	while(layout->nb_of_non_redirect_splitable_chars-- >= 0)
	{
		program = ft_substr(line, cmd_start, cmd_end - cmd_start);
		//if (is_line_empty(program))
		//{
		//	printf("%sError ma boi (wrong syntax)\n", MINISHELL_PROMPT);
		//	return (NULL);
		//}

		
		//if (layout->nb_of_splitable_chars == -1) // Last program
		//	redirect_type = REDIRECT_STDOUT;
		

		//re_parse(program);
		char **args = parse_program_and_args(program);
		get_first_redirection_file(args);
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
	t_cmd			*cmds;
	int				i;
	t_cmd_layout	layout;

	layout.nb_of_splitable_chars = 0;
	layout.nb_of_non_redirect_splitable_chars = 0;
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