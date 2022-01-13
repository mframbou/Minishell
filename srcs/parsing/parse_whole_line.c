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
	 PIPE_CHAR = 1,
	 OR_CHAR = 2,
	 SINGLE_AMPERSTAND =  3, // &&
	 DOUBLE_AMPERSTAND = 4, // &&
	 AND_CHAR = 5,
	 SINGLE_LEFT_REDIRECT = 6,
	 DOUBLE_LEFT_REDIRECT = 7,
	 SINGLE_RIGHT_REDIRECT = 8,
	 DOUBLE_RIGHT_REDIRECT = 9
}	t_splitable_char;

int is_splitable_char(char c)
{
	if ( c == '|' || c == '>' || c == '<' || c == '&')
		return 1;
	return 0;
}

void set_layout_char(t_cmd_layout *layout, char* line, int *index)
{
	if(line[*index] == '|')
	{
		if(line[*index + 1] == '|' && line[*index + 1])
		{
			layout->splitable_char[*index] = OR_CHAR;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
			(*index)++;
		}
		else
		{
			layout->splitable_char[*index] = PIPE_CHAR;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
		}
	}		
	if(line[*index] == '>')
	{
		if(line[*index + 1] == '|' && line[*index + 1])
		{
			layout->splitable_char[*index] = DOUBLE_RIGHT_REDIRECT;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
			*index++;
		}
		else
		{
			layout->splitable_char[*index] = SINGLE_RIGHT_REDIRECT;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
		}
	}		
	if(line[*index] == '<')
	{
		if(line[*index + 1] == '<' && line[*index + 1])
		{
			layout->splitable_char[*index] = DOUBLE_LEFT_REDIRECT;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
			*index++;
		}
		else
		{
			layout->splitable_char[*index] = SINGLE_LEFT_REDIRECT;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
		}
	}	
	if(line[*index] == '&')
	{
		if(line[*index + 1] == '<' && line[*index + 1])
		{
			layout->splitable_char[*index] = DOUBLE_AMPERSTAND;
			layout->splitable_char_pos[*index] = *index;
			*index++;
			layout->nb_of_splitable_chars++;
		}
		else
		{
			layout->splitable_char[*index] = SINGLE_AMPERSTAND;
			layout->splitable_char_pos[*index] = *index;
			layout->nb_of_splitable_chars++;
		}

	}		
}

create_cmd_layout(t_cmd_layout *layout, char *line)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(line[i])
	{
		if (is_splitable_char(line[i]))
		{
			j = i;
			while(is_splitable_char(line[j]) && line[j])
			{
				set_layout_char(layout,line,&j);
				j++;
			}
		}
		i++;
	}
}

t_cmd **split_cmds(t_cmd_layout *layout, char *line)
{
	
	t_cmd cmds;
	int i;

	i = 0;
	while(--(layout->nb_of_splitable_chars))
	{
		
	}
	
}

t_cmd	*parse_cmds(char *line)
{
	char	**cmds;
	int		i;
	t_cmd_layout layout;

	create_cmd_layout(&layout, line);
	cmds = split_cmds(&layout, line);
	//cmds = ft_split(line, '|'); // TODO: Better parsing (more error checks, <<, <, > and >> characters)

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

