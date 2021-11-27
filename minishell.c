/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:45:12 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/27 12:57:26 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define PATH_STR "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

void	parse(char *str);

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
		add_env_variable("PATH", ft_strdup(PATH_STR));
}

int	main(int argc, char *argv[])
{
	char	*line;

	init_basic_env_variables();
	while (1)
	{
		line = readline("minishell: ");
		if (line)
			execute_command(parse_program_and_args(line));
	}
}
