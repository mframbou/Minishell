/* ************************************************************************** */
/*                                                                           */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created:   by            `-'                        `-'                  */
/*   Updated:   by                                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_closed_quote(char *str)
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

static char	*get_line_till_space_or_quote(char *str)
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
static char	*get_line_till_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

static char	*get_line_till_any_quote(char *str)
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

/*
	Retrieve the argument, only special case is if the arg == '' or ""
	In which case we just do i += 2 to skip the quotes and return NULL since it's like an empty arg
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
			res = get_line_till_any_quote(&(str[*i]));
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
/*
	This function in only called if a $ sign is found

	It goes to the $ (copy every char on the way)
	Then copy the value of the variable (or nothing if the variable is not in the env)
	Then copy the second part of the string (starting from the end of the $VAR)
*/
static char *interpret_one_dollar_var(char *str, int i)
{
	int	start_index;
	int	end_index;
	char *env_name;
	char *env_value;
	char *result;

	i++;
	start_index = i;
	// Continue while our variable is valid
	// if it's not, return a copy since we free the original in our "parent" / calling function
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return(ft_strdup(str));
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	end_index = i;
	env_name = ft_substr(str,start_index, end_index - start_index);
	env_value = get_env_variable(env_name);

	// If the env value is valid, then our total size = strlen - env variable length ($ARG) + env value length ("Test variable")
	// If not, then it's just the strlen - env variable length ($ARG)
	// Since if our value is null (no associated variable) strlen(NULL) = 0, we can use the same formula
																					/* env_val == NULL ? 0 : strlen */
	int total_res_size = (sizeof(char) * (ft_strlen(str) - (ft_strlen(env_name) + 1) + ft_strlen(env_value) + 1));
	result = malloc(sizeof(char) * total_res_size);
	int j = 0;
	// Copy the first part in both cases
	while(str[j] && str[j] != '$')
	{
		result[j] = str[j];
		j++;
	}
	// Set null terminated for strlcat (start point for the cat)
	result[j] = '\0';

	// If we have a variable to replace, append it
	if (env_value)
		ft_strlcat(result, env_value, total_res_size);
	
	// Then "skip" our $ARG (since we replaced it with the variable value)
	// which is strlen(env_name) ("ARG" = 3) + 1 ('$') => $ARG = 4
	j += (ft_strlen(env_name) + 1);

	// Then append the second part
	ft_strlcat(result, &(str[j]), total_res_size);

	// Free env name, if it's null it will simply do nothing
	free(env_name);
	return (result);
}

static char	*get_unquoted_arg(char *str)
{
	char	*res;

	// If there are quotes AND they are closed, then remove them, else don't do anything
	if (str && (str[0] == '\'' || str[0] == '"') && is_closed_quote(&str[0]))
	{
		res = ft_substr(str, 1, ft_strlen(str) - 2);
		free(str);
	}
	else
		res = str;
	return (res);
}

static char	*interpret_env_arg(char *str)
{

	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	// If it's a string starting with simple quotes, don't interpret it, otherwise interpret $ signs
	// except if it's an unclosed quote
	// But in both case if it has quotes at the start and end remove them
	if (str[0] == '\'' && is_closed_quote(&(str[0])))
		return (str);
	else
	{
		result = ft_strdup(str);
		while(str[i])
		{
			if (str[i] == '$')
			{
				tmp = result;
				result = interpret_one_dollar_var(tmp, i);
				free(tmp);
			}
			i++;
		}
		free(str);
	}
	return get_unquoted_arg(result);
}

// Takes pointer to array of string (triple pointer)
void	interpret_all_args(char	***args)
{
	int	i;

	i = 0;
	while ((*args)[i])
	{
		(*args)[i] = interpret_env_arg((*args)[i]);
		i++;
	}
}


char	**remove_empty_args(char **args)
{
	int		valid_count;
	int		i;
	int		j;
	char	**new_args;

	valid_count = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			valid_count++;
		i++;
	}
	new_args = (char **) malloc(sizeof (char *) * (valid_count + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			new_args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	free(args);
	new_args[j] = NULL;
	return (new_args);
}


char	**parse_program_and_args(char *line)
{
	char	**args;
	char	*current_arg;
	char	*new_line;
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	args = (char **) malloc(sizeof(char *) * (count_args(line) + 1));
	if (!args)
		return (NULL);
	new_line = ft_strtrim(line, " \t\v\f\r");
	free(line);
	while (new_line[i])
	{
		while (new_line[i] && ft_isspace(new_line[i]))
			i++;
		if (!new_line[i])
			break ;
		current_arg = get_one_arg(new_line, &i);
		if (current_arg)
		{
			args[argc++] = current_arg;
			i += ft_strlen(current_arg);
		}
	}
	args[argc] = NULL;
	interpret_all_args(&args);
	args = remove_empty_args(args);
	return (args);
}

// // salut '$variable oronda' "$variable oronda"
// int main()
// {
// 	add_env_variable(ft_strdup("TEST"), ft_strdup("Grosse merde"));
// 	char *line = ft_strdup("\"Salut\" '' \"$TEST ''$_-TEST'\"");
// 	char **res = parse_program_and_args(line);
// 
// 
// 	// input string = \"Salut\" '' \"$TEST ''$_-TEST'\"
// 	int i = 0;
// 	while(res[i])
// 	{
// 		res[i] = interpret_env_arg(res[i]);
// 		i++;
// 	}
// 	/*
// 		res[0] = "Salut"
// 		res[1] = "Grosse merde ''EST'"
// 		res[2] = NULL
// 	*/
// 	return 0;
// }

t_cmd	**get_cmd_lst(void)
{
	static t_cmd *cmd_lst = NULL;

	return (&cmd_lst);
}

void	add_cmd(char **args)
{
	t_cmd	**cmd_lst;

	cmd_lst = get_cmd_lst();
	add_cmd_to_lst(cmd_lst, create_cmd(args));
}

void	clear_cmds(void)
{
	t_cmd	**cmd_lst;
	t_cmd	*curr;
	t_cmd	*prev;

	cmd_lst = get_cmd_lst();
	curr = *cmd_lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		prev->next = NULL;
		free_ft_split(prev->args);
		free(prev);
	}
	*cmd_lst = NULL;
}


t_cmd	*parse_cmds(char *line)
{
	char	**cmds;
	int		i;

	cmds = ft_split(line, '|');
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
