#include "../minishell.h"

int	is_closed_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
		return (0);
	return (i);
}

/*
	If we found a non-closing quote, then count it as part of the argument
*/
//char	*get_line_till_space_or_quote(char *str)
//{
//	int	i;
//	int	j;
//	int	closed_quote_found;
//
//	i = 0;
//	closed_quote_found = 0;
//	while (str[i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '"')
//		i++;
//	if (str[i] == '"' || str[i] == '\'')
//	{
//		if (is_closed_quote(&(str[i])))
//			return (ft_substr(str, 0, i));
//		else
//		{
//			i++;
//			while (str[i] && !ft_isspace(str[i]) && \
//			str[i] != '"' && str[i] != '\'')
//				i++;
//			if (str[i] == '"' || str[i] == '\'')
//			{
//				if (is_closed_quote(&(str[i])))
//					return (ft_substr(str, 0, i));
//				else
//				{
//					while (str[i] && !ft_isspace(str[i]))
//						i++;
//					return (ft_substr(str, 0, i));
//				}
//			}
//			else
//				return (ft_substr(str, 0, i));
//		}
//	}
//	return (ft_substr(str, 0, i));
//}

char	*get_line_till_space_or_quote(char *str)
{
	int	i;
	int	j;
	int	closed_quote_found;

	i = 0;
	closed_quote_found = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i] == '"' || str[i] == '\'')
	{
		if (!is_closed_quote(&(str[i])))
		{
			i++;
			while (str[i] && !ft_isspace(str[i]) && str[i] != '"' && str[i] != '\'')
				i++;
			if ((str[i] == '"' || str[i] == '\'') && !is_closed_quote(&(str[i])))
				while (str[i] && !ft_isspace(str[i]))
					i++;
		}
	}
	return (ft_substr(str, 0, i));
}

/*
	test"i' ca' marche ou pas ?

	special case
*/
char	*get_line_till_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_line_till_any_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (ft_substr(str, 1, i - 1));
}

char	*get_line_till_quote(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	return (ft_substr(str, 1, i - 1));
}

/*
	Bash variable names consist only of letters, digits or underscore,
	and cannot start with a digit
*/
/*
char	*extract_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i])
		}
		i++;
	}
}
*/
/*
char	*replace_env_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			
		}
	}
}
*/

static char	*get_one_arg(char *str, int *i)
{
	char	*res;
	int		closed_quote_distance;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		closed_quote_distance = is_closed_quote(&(str[*i]));
		if (closed_quote_distance == 0)
			res = get_line_till_space(&(str[*i]));
		else if (closed_quote_distance == 1)
		{
			*i += 2;
			return (NULL);
		}
		else
		{
			res = get_line_till_any_quote(&(str[*i]));
			*i += 2;
		}
	}
	else
		res = get_line_till_space_or_quote(&str[*i]);
	return (res);
}

static int	count_args(char *old_line)
{
	char	*current_arg;
	char	*line;
	int		i;
	int		count;

	i = 0;
	count = 0;
	line = ft_strtrim(old_line, " \t\v\f\r");
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		current_arg = get_one_arg(line, &i);
		if (current_arg)
		{
			i += ft_strlen(current_arg);
			count++;
			free(current_arg);
		}		
	}
	free(line);
	return (count);
}

char	**parse(char *old_line)
{
	char	**args;
	char	*current_arg;
	char	*line;
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	args = (char **) malloc(sizeof(char *) * (count_args(old_line) + 1));
	if (!args)
		return (NULL);
	line = ft_strtrim(old_line, " \t\v\f\r");
	free(old_line);
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		current_arg = get_one_arg(line, &i);
		if (current_arg)
		{
			args[argc++] = current_arg;
			i += ft_strlen(current_arg);
		}
	}
	args[argc] = NULL;
	return (args);
}

//int main()
//{
//	char *line = ft_strdup(" salut 'oronda tu es' "" bg ' ' et magnifique");
//	char **res = parsing(line);
//	return 0;
//}
