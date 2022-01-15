/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 15-01-2022 02:20 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*interpret_one_dollar_var_2(char *src, int res_size, \
										char *env_name, char *env_value, int dollar_index);

/*
	This function in only called if a $ sign is found

	It goes to the $ (copy every char on the way)
	Then copy the value of the variable 
		(or nothing if the variable is not in the env)
	Then copy the second part of the string 
		(starting from the end of the $VAR)

	Basically: "cat $file $user" becomes "cat file.txt $user"
	Then called another time to become "cat file.txt oronda"

	Code logic:
	(Part 1)
	- If variable is not valid (eg. $+test) => return it as it
	- If it is but not entirely (eg. test_+-+- => "test_")
		(just like real bash)
	- Then retrieve the associated value in the env 
		(if any, if not "$FOO" becomes "") and :
	
	(Part 2)
	- re-allocate the string
		to add the new value (basically we replace our "$FOO" with "bar") 
		(strlen returns 0 if str is NULL)
	This is done by copying the first part of our string, then the "bar" value 
		(again if any), then the second part of the string
	- env_name = ($)FOO
	- env_value = bar
	- "echo $FOO"
	         ^ ^---- end index
			start index
	- result = "echo bar"

	Also "skip" the value of the $val with the index (set it to after the value name)
*/
static char	*interpret_one_dollar_var(char *str, int *index)
{
	int		start_index;
	int		end_index;
	char	*env_name;
	char	*env_value;
	int		res_size;

	(*index)++;
	start_index = *index;
	if (ft_isalpha(str[*index]) || str[*index] == '_')
		(*index)++;
	else
		return (ft_strdup(str));
	while (str[*index] && \
	(ft_isalpha(str[*index]) || ft_isdigit(str[*index]) || str[*index] == '_'))
		(*index)++;
	end_index = (*index);
	env_name = ft_substr(str, start_index, (end_index - start_index));
	env_value = get_env_variable(env_name);
	res_size = (sizeof(char) * (ft_strlen(str) - (ft_strlen(env_name) + 1) \
				+ ft_strlen(env_value) + 1));
	*index = start_index - 1 + ft_strlen(env_value); // startindex-1 = '$' sign (start of env variable replacement) This takes our original index form '$' to the end of the expanded value
	return (interpret_one_dollar_var_2(str, res_size, env_name, env_value, start_index - 1)); // give the dollar index instead of beginning because we could be in a case where we have '$FOO' "$BAR" and we only want to interpret $BAR
}

static char	*interpret_one_dollar_var_2(char *src, int res_size, \
										char *env_name, char *env_value, int dollar_index)
{
	char	*result;
	int		j;

	result = malloc(sizeof(char) * res_size);
	j = 0;
	while (src[j] && j < dollar_index)
	{
		result[j] = src[j];
		j++;
	}
	result[j] = '\0';
	if (env_value)
		ft_strlcat(result, env_value, res_size);
	j += (ft_strlen(env_name) + 1);
	ft_strlcat(result, &(src[j]), res_size);
	free(env_name);
	return (result);
}

/*
	If there are quotes AND they are closed -> remove them, otherwise keep them

	Realloc the string directly
*//* NEW FUNCTION interpret_quotes (char **str)
char	*get_unquoted_arg(char *str)
{
	char	*res;

	if (str && (str[0] == '\'' || str[0] == '"') && is_closed_quote(&str[0]))
	{
		res = ft_substr(str, 1, ft_strlen(str) - 2);
		free(str);
	}
	else
		res = str;
	return (res);
}*/

/*
	If it's a string starting with simple quotes, don't interpret it,
		otherwise interpret $ signs
	except if it's an unclosed quote
	But in both case if it has quotes at the start and end remove them


	Echo "test $PATH '$PATH'"
	=> echo "test /usr/bin:/usr/sbin '/usr/bin:/usr/sbin'"

	echo pouet > salut'$PATH""'"$HOME".txt''
	echo pouet > salut'$PATH""'"/home/mframbo"
				                ^           ^
							    15         27

	final res expected = salut$PATH""/Users/mframbou.txt
*/
char	*interpret_env_args(char *str)
{
	char	*tmp;
	int		i;
	int		is_in_double_quote;

	i = 0;
	is_in_double_quote = 0;
	while (str[i])
	{
		//printf("current char : %c [%d]\n", str[i], i);
		if (str[i] == '\'')
		{
			if (!is_in_double_quote)
				i += is_closed_quote(&(str[i])); // Skip the single quotes if they are not inside double quotes (variable should_be_interpreted, false = skip, true = interpret)
			// No need to do i++ since it's executed at the end of the while
		}
		else if (str[i] == '"') // Everytime we hit a double quotes which closes, toggle the variable, first time means everything in the double quotes should be interpreted, and when exiting the quotes it shouldn't anymore
		{
			if (!is_in_double_quote && is_closed_quote(&(str[i])))
				is_in_double_quote = 1;
			else if (is_in_double_quote)
				is_in_double_quote = 0;
		}
		else if (str[i] == '$')
		{
			tmp = str;
			str = interpret_one_dollar_var(tmp, &i); // Replace $FOO with bar and moves the index from '$' to right after "bar"
			free (tmp);
			continue ;
		}
		i++;
	}
	interpret_quotes(&str);
	return (str);
	/*
	if (str[0] == '\'' && is_closed_quote(&(str[0])))
		return (str);
	else
	{
		result = ft_strdup(str);
		while (str[i])
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
	return (get_unquoted_arg(result));
	//return (result);
	*/
}
