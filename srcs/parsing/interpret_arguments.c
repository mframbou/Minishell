/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 27-01-2022 13:51 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	Also set the index at the index to right after $VAR (Before in was on '$')
		(start_index - 1 = initial index ($ char), so add the length of the
		replace variable (foo = length 3)) so that our loop can continue easily
	Give the dollar char index to the second part of the function so that
	instead of searching for the first '$' (which might be in quotes) we already
	have it
*/
static char	*interpret_one_dollar_var_2(char *src, int res_size, \
										char *env_name, int dollar_char_index);

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
	*index = start_index - 1 + ft_strlen(env_value);
	return (interpret_one_dollar_var_2(str, res_size, env_name, \
										start_index - 1));
}

static char	*interpret_one_dollar_var_2(char *src, int res_size, \
										char *env_name, int dollar_char_index)
{
	char	*result;
	int		j;
	char	*env_value;

	result = ft_malloc(sizeof(char) * res_size);
	j = 0;
	while (src[j] && j < dollar_char_index)
	{
		result[j] = src[j];
		j++;
	}
	result[j] = '\0';
	env_value = get_env_variable(env_name);
	if (env_value)
		ft_strlcat(result, env_value, res_size);
	j += (ft_strlen(env_name) + 1);
	ft_strlcat(result, &(src[j]), res_size);
	return (result);
}

/*
	If there are quotes AND they are closed -> remove them, otherwise keep them

	Realloc the string directly

	NEW BETTER FUNCTION interpret_quotes (char **str)
	this one is deprecated but we keep it just in case

char	*get_unquoted_arg(char *str)
{
	char	*res;

	if (str && (str[0] == '\'' || str[0] == '"') && is_closed_quote(&str[0]))
	{
		res = ft_substr(str, 1, ft_strlen(str) - 2);
		//free(str);
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

	If we have simple quotes inside double quotes (eg. "test '$PATH'")"
	We still need to interpret the $PATH (since simple quotes are inside
	double they just count as regular character, that's why the variable
	is_in_double_quotes exists)
*/

/*
	Just for norminette, if we are in doubles quotes return 1, if we just left
	double quotes, return 0, otherwise nothing changed
*/
static int	check_if_in_double_quotes(int is_in_double_quotes, char *quotes_str)
{
	if (!is_in_double_quotes && is_closed_quote(quotes_str))
		return (1);
	else if (is_in_double_quotes)
		return (0);
	return (is_in_double_quotes);
}

static void	interpret_dollar_var_and_free(char **str, int *index)
{
	char	*tmp;

	tmp = *str;
	*str = interpret_one_dollar_var(tmp, index);
	ft_free(tmp);
}

char	*interpret_env_args(char *str)
{
	int		i;
	int		is_in_double_quote;

	i = 0;
	is_in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_in_double_quote)
			i += is_closed_quote(&(str[i]));
		else if (str[i] == '"')
			is_in_double_quote = check_if_in_double_quotes(is_in_double_quote, \
															&(str[i]));
		else if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				str = insert_last_exit_status(str, &i);
			else
				interpret_dollar_var_and_free(&str, &i);
			continue ;
		}
		i++;
	}
	interpret_quotes(&str);
	return (str);
}
/* Old version of this function (with issues)
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
				//free(tmp);
			}
			i++;
		}
		//free(str);
	}
	return (get_unquoted_arg(result));
	//return (result);
*/
