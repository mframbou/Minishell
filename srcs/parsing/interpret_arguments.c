/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/01/20 00:00:00 by ' \/ (   )/       #+#    #+#             */
/*   Updated: 2022/01/14 15:21:58 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*interpret_one_dollar_var_2(char *src, int res_size, \
										char *env_name, char *env_value);

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
*/
static char	*interpret_one_dollar_var(char *str, int i)
{
	int		start_index;
	int		end_index;
	char	*env_name;
	char	*env_value;
	int		res_size;

	i++;
	start_index = i;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return (ft_strdup(str));
	while (str[i] && \
	(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	end_index = i;
	env_name = ft_substr(str, start_index, (end_index - start_index));
	env_value = get_env_variable(env_name);
	res_size = (sizeof(char) * (ft_strlen(str) - (ft_strlen(env_name) + 1) \
				+ ft_strlen(env_value) + 1));
	return (interpret_one_dollar_var_2(str, res_size, env_name, env_value));
}

static char	*interpret_one_dollar_var_2(char *src, int res_size, \
										char *env_name, char *env_value)
{
	char	*result;
	int		j;

	result = malloc(sizeof(char) * res_size);
	j = 0;
	while (src[j] && src[j] != '$')
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
*/
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
}

/*
	If it's a string starting with simple quotes, don't interpret it,
		otherwise interpret $ signs
	except if it's an unclosed quote
	But in both case if it has quotes at the start and end remove them
*/
char	*interpret_env_arg(char *str)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
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
	return (result);
}
