#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

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
	return (ft_substr(str, 0, i + 1));
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

char	**parsing(char *old_line)
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

char *interpret_dollar(char *str, int i)
{
	int	start_index;
	int	end_index;
	char *env_name;
	char *env_value;
	char *result;


	i++;
	start_index = i;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return(str);
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	end_index = i;

	env_name = ft_substr(str,start_index,end_index - start_index);
	env_value = get_env_variable(env_name);
	if(env_value)
	{
		int res_size = (sizeof(char) * (ft_strlen(str) - (ft_strlen(env_name) + 1) + ft_strlen(env_value)));
		result = malloc(sizeof(char) * res_size + 1);
		ft_bzero(result, sizeof(char) * res_size + 1);
		free(env_name);
		
		int j = 0;

		while(str[j] && str[j] != '$')
		{
			result[j] = str[j];
			j++;
		}
		ft_strlcat(result, env_value, res_size);
		ft_strlcat(result, &(str[j + ft_strlen(env_name)]), res_size);
	}
	else
	{

	}






	//while(str[i] && !ft_isspace(str[i]))

}


char	*transform_env_arg(char *str)
{

	char *result;
	int	i;
	i = 0;

	if (str[0] == '\'')
		return (str);
	else
	{
		while(str[i])
		{
			if (str[i] == '$')
			{
				str = interpret_dollar(str, i);
			}
			i++;
		}
		
		
		
		
	}
	return str;
}

// salut '$variable oronda' "$variable oronda"
int main()
{
	add_env_variable(ft_strdup("TEST"), ft_strdup("Grosse merde"));
	char *line = ft_strdup("\"Salut $TEST-Mais t'es bg\"");
	char **res = parsing(line);
	int i = 0;
	char *test = transform_env_arg(res[0]);
	/*
	while(res[i])
	{
		interpret_env_arg(res[i]);
		i++;
	}
	*/
	return 0;
}
