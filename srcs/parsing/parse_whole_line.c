/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 13-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 15-01-2022 02:20 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
	int operator_chars[4096];
	int operators_nb;
	int	non_redirect_operators_nb;
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

static void	layout_pipe(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '|' && line[(*index) + 1])
	{
		layout->operator_chars[(*index)] = OR_CHAR;
		layout->operators_nb++;
		layout->non_redirect_operators_nb++;
		((*index))++;
	}
	else
	{
		layout->operator_chars[(*index)] = PIPE_CHAR;
		layout->operators_nb++;
		layout->non_redirect_operators_nb++;
	}
}

static void layout_right_redirect(t_cmd_layout *layout, char *line, int *index)
{
	if (line[(*index) + 1] == '>' && line[(*index) + 1])
	{
		layout->operator_chars[(*index)] = DOUBLE_RIGHT_REDIRECT;
		layout->operators_nb++;
		(*index)++;
	}
	else
	{
		layout->operator_chars[(*index)] = SINGLE_RIGHT_REDIRECT;
		layout->operators_nb++;
	}
}
static void layout_left_redirect(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '<' && line[(*index) + 1])
	{
		layout->operator_chars[(*index)] = DOUBLE_LEFT_REDIRECT;
		layout->operators_nb++;
		(*index)++;
	}
	else
	{
		layout->operator_chars[(*index)] = SINGLE_LEFT_REDIRECT;
		layout->operators_nb++;
	}
}
static void layout_and(t_cmd_layout *layout, char *line, int *index)
{
	if(line[(*index) + 1] == '&' && line[(*index) + 1])
	{
		layout->operator_chars[(*index)] = AND_CHAR;
		(*index)++;
		layout->operators_nb++;
		layout->non_redirect_operators_nb++;
	}
}

static void set_layout_char(t_cmd_layout *layout, char* line, int *index)
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

	layout->non_redirect_operators_nb = 0;
	layout->operators_nb = 0;
	ft_bzero(layout->operator_chars, 4096);
	i = 0;
	while(line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && is_closed_quote(&line[i]))
			i += is_closed_quote(&line[i]) + 1; // Goes after the second quote
		if (!line[i])
			break;
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
	Takes our line (eg. echo "test" > test.txt | cat)
                                    ^          ^
				cmd layout =>  RIGHT_REDIR    PIPE

	Returns a list of commands (just separated on |, || and &&)
	(in this case "echo "test" > test.txt", "cat")
*/
static int	is_not_redirection_operator(char c)
{
	return (c == PIPE_CHAR || c == OR_CHAR || c == AND_CHAR);
}

static int	get_operator_str_len(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (2);
}

static int	get_next_non_redirect_operator(char *line, int index, t_cmd_layout layout)
{
	while (line[index] \
	&& !is_not_redirection_operator(layout.operator_chars[index]))
		index++;
	return (index);
}

/*
	Input = "echo test | cat > test.txt"

	Output = ["echo test", "cat > test.txt"]
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
	cmd_end = get_next_non_redirect_operator(line, 0, layout);
	programs_list = malloc(sizeof(char *) * (layout.non_redirect_operators_nb + 2)); // If 1 program, our redirect nb = 0, so malloc 2 (1 prog + NULL at the end)
	while (layout.non_redirect_operators_nb-- >= 0)
	{
		programs_list[i++] = ft_substr(line, cmd_start, cmd_end - cmd_start);
		cmd_start = cmd_end + get_operator_str_len(layout.operator_chars[cmd_end]);
		if (line[cmd_end])
			cmd_end++; // Skip the current operator to go to the next cmd
		cmd_end = get_next_non_redirect_operator(line, cmd_end, layout);
	}
	programs_list[i] = NULL;
	return (programs_list);
}


static int	is_redirection_operator(int operator)
{
	return (operator == SINGLE_LEFT_REDIRECT \
	|| operator == SINGLE_RIGHT_REDIRECT \
	|| operator == DOUBLE_LEFT_REDIRECT \
	|| operator == DOUBLE_RIGHT_REDIRECT);
}

static int	get_next_redirect_operator(char *line, int index, t_cmd_layout layout)
{
	while (line[index] \
	&& !is_redirection_operator(layout.operator_chars[index]))
		index++;
	return (index);
}

static int	get_next_redirect_operator_index(char *line, int current_index)
{
	t_cmd_layout	layout;

	create_cmd_layout(&layout, line);
	return (get_next_redirect_operator(line, current_index, layout));
}

/*
	"echo test > test.txt > prout> salut.txt"


	"salut.txt"
	"echo test"
	
	Takes a pointer to the arg list (because it modifies it)

	Return the filename if found, otherwise NULL

	"Salut", 2
	=> "Saut"

	"Sa"
	"ut"

	"Test", 3
	"Tes"

	"test", 0
	"est"

	Temporarily replace char with '\0' for easier strlcat
*/
static char	*remove_char_from_string(char *str, int index)
{
	char	*res;
	int		new_len;
	char	old_char;

	if (index > ft_strlen(str) - 1 || index < 0)
		return (str);
	new_len = ft_strlen(str) - 1;
	res = malloc(sizeof(char) * (new_len + 1));
	ft_bzero(res, new_len + 1);
	old_char = str[index];
	str[index] = '\0';
	ft_strlcat(res, str, new_len + 1);
	str[index] = old_char;
	ft_strlcat(res, str + index + 1, new_len + 1);
	free(str);
	return (res);
}

// > t
// ^ ^
char	*remove_substr(char *str, int start, int end)
{
	while (--end >= start)
		str = remove_char_from_string(str, start);
	return (str);
}


/*
	From : "Hello "test""
	To: Hello test

	As real bash

	If double quotes are in simple quotes, keep them

	salut.'"test"''

	i = 6, str[i] = '
	is_closed_quote = 7

	newstr = salut."test"''
	newstr = salut."test"'

	i += 7-1 = 6 + 6 = 12

	result should be = salut."test"'
	
*/
void	interpret_quotes(char **str)
{
	int	i;
	int	end_quote;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'') // If we have single quotes, don't interpret anything inside of it
		{
			end_quote = is_closed_quote(&((*str)[i]));
			if (end_quote)
			{
				*str = remove_char_from_string(*str, i);
				*str = remove_char_from_string(*str, i + end_quote - 1);// since we removed 1 quote, closing quote is previous character than before
				i += end_quote - 1;	// echo 'test' => echo test
									//      ^-- i=5            ^-- i=9 end_quote = 5, new i = old_i + end_quote - 2; 9 = 5 + 5 - 1
				continue;
			}
			
		}
		else if ((*str)[i] == '"')
		{
			end_quote = is_closed_quote(&((*str)[i]));
			if (end_quote)
			{
				*str = remove_char_from_string(*str, i);
				*str = remove_char_from_string(*str, i + end_quote - 1);// since we removed 1 quote, closing quote is previous character than before
				i += end_quote - 1;	// echo 'test' => echo test
				continue ;
			}
		}
		i++;
	}
}

/*
	Takes pointer to line

	Extract the filename and remove it from the line

	"echo > test.txt" => Return: "test.txt", line = "echo"
*/
char	*get_first_redirection_filename(char **line)
{
	int		i;
	int		j;
	char	*filename;

	filename = NULL;
	i = get_next_redirect_operator_index((*line), 0);
	if ((*line)[i]) // If we have a redirection
	{
		i += get_operator_str_len((*line)[i]);	// Skip the operator
		while ((*line)[i] && ft_isspace((*line)[i]))
			i++;
		if (!(*line)[i])
		{
			printf("TODO NO FILENAME\n");
			return (NULL);
		}
		filename = &((*line)[i]);
		j = 0;
		while (filename[j] && !(ft_isspace(filename[j]) || !is_valid_in_filename(filename[j]))) // If there is '>' or '|' or ':' or whatever not valid that is not in quotes, we interpret it, if it's in quote it get skipped
		{
			if (filename[j] == '"' || filename[j] == '\'')
				j += is_closed_quote(&(filename[j])); // If is not closed quote, stay here, if it is, simply skip it (this allow to have spaces in filename)
			j++;
		}
		filename = ft_substr(filename, 0, j); // Retrieve our filename of j size
		(*line) = remove_substr((*line), get_next_redirect_operator_index((*line), 0), i + j); // j = filename size
		// interpret_quotes(&filename); TODO: put this after, first interpret env args if any, then remove any quotes left
	}	
	return (filename);
}


/*
	Takes pointer to program line


	echo test > Salut'olivie"r'.t"xt''"'
	should create file name: Salutolivie"r.txt'''


	echo test > salut'$PATH""'"$HOME".txt''
	should search for salut$PATH""$HOME.txt
	which expands to salut$PATH""/Users/mframbou.txt
*/
int	create_files_and_return_output_fd(char **line)
{
	char	*filename;
	char	*prev_filename;
	int		fd;

	filename = get_first_redirection_filename(line);
	prev_filename = NULL;
	fd = -1;
	while (filename)
	{
		prev_filename = filename;
		printf("filename from parsing: %s\n", filename);
		filename = interpret_env_args(filename);
		printf("interpreted filename: %s\n", filename);
		interpret_quotes(&filename);
		fd = open (filename, O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
			return(perror_return("Error while opening file"));
		filename = get_first_redirection_filename(line);
		if (filename) // If we have another file, else keep the fd opened
			close(fd);
	}
	return (fd);
}
/*
	Takes our line return a list of fully parsed programs

	when interpreting args, put "" aronud the value for easier parsing
*/
t_cmd	*parse_cmds(char *line)
{
	t_cmd	*commands;
	char	**cmds;
	int		redirect_fd;

	cmds = split_command_operands(line);
	
	for (int i = 0; cmds[i]; i++)
	{
		redirect_fd = create_files_and_return_output_fd(&(cmds[i]));
		if (redirect_fd >= 0)
			write(redirect_fd, "Salut pouet", 12);
		// Need to add command with correct redirection type, redirection fd and args
		// parse_program_and_args for args, redirect_fd for fd, need a function for redirection type
	}

	
		
	//interpret_all_args(&args); // Puts quotes around every arg, must remove it after parsing redirection
	//return(0);
	//for (int i = 0; args[i]; i++)
	//{
	//	printf("arg=\"%s\"\n", args[i]);
	//}
	//printf("\n");
	return (commands);
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
