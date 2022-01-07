/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:45:12 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 11:41:20 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	**parse(char *str);

int	is_line_empty(char *str)
{
	while (ft_isspace(*str) && *str)
		str++;
	if (*str)
		return (0);
	return (1);
}

void	init_basic_env_variables(void)
{
	char	*home_env;
	char	*path_env;

	home_env = getenv("HOME");
	path_env = getenv("PATH");
	if (home_env)
		add_env_variable("HOME", ft_strdup(home_env));
	else
		add_env_variable("HOME", ft_strdup("/"));
	if (path_env)
		add_env_variable("PATH", ft_strdup(path_env));
	else
		add_env_variable("PATH", ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"));
}

int	main(int argc, char *argv[])
{
	char	*line;

	init_basic_env_variables();
	while (1)
	{
		line = readline("Minishell::::");
		if (line && line[0] != '\0' && !is_line_empty(line))
		{
			add_history(line);
		}
		char **args = parse(line);
		for (int i = 0; args[i]; i++)
		{
			printf("%s\n", args[i]);
			
		}
	}
}
