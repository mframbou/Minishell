/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:58:30 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/07 18:01:14 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>

/*
	Max path length is PATH_MAX bytes
	https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_271
*/

int	is_non_forked_command(char *program)
{
	static char	*envs[] = {"export", "unset", "env", "cd", "pwd", "exit", NULL};
	int			i;

	i = 0;
	while (envs[i])
		if (strcmp(envs[i++], program) == 0)
			return (1);
	return (0);
}

int	is_forked_command(char *program)
{
	static char	*builtins[] = {"echo", NULL};
	int			i;

	i = 0;
	while (builtins[i])
		if (strcmp(builtins[i++], program) == 0)
			return (1);
	return (0);
}

void	exec_non_forked_command(char **args)
{
	if (strcmp(args[0], "export") == 0)
		export_command(args);
	else if (strcmp(args[0], "unset") == 0)
		unset_command(args);
	else if (strcmp(args[0], "env") == 0)
		env_command();
	else if (strcmp(args[0], "cd") == 0)
		cd_cmd(args);
	else if (strcmp(args[0], "pwd") == 0)
		pwd_cmd();
	//else if (strcmp(args[0], "exit") == 0)
	//	env_command();
}

void	exec_forked_command(char **args)
{
	// char **env = get_env_as_string_array();
	// printf("ENV:\n");
	// for (int i = 0; env[i]; i++)
	// {
	// 	printf("%s\n", env[i]);
	// }
	int return_val;
	char	*program_path;
	int		program_path_len;

	program_path_len = (ft_strlen("execs/") + ft_strlen(args[0]) + 1);
	program_path = (char *) malloc(sizeof(char) * program_path_len);
	ft_bzero(program_path, program_path_len);
	ft_strlcat(program_path, "execs/", program_path_len);
	ft_strlcat(program_path, args[0], program_path_len);
	if (fork() == 0)
	{
	// PATH:/usr/bin
	// /usr/bin
		execve(program_path, args, get_env_as_string_array());
		printf("Just executed %s\n", args[0]);
	}
	else
	{
		waitpid(-1, &return_val, 0);
		printf("Returned value: %d\n", return_val);
	}
	free(program_path);
}

// /bin:/oronda::/bin
// [/bin, /oronda, /bin]
int	does_program_exists(char *program)
{
	char			*path;
	char			**paths;
	int				i;
	char			full_path[PATH_MAX];
	int				res;
	int				file_found;

	path = get_env_variable("PATH");
	if (!path)
	{

	}
	else
	{
		paths = ft_split(path, ':');
		i = 0;
		while (paths[i])
		{
			ft_bzero(full_path, PATH_MAX);
			if (!is_line_empty(paths[i]))
			{
				ft_strlcpy(full_path, paths[i], PATH_MAX);
				ft_strlcat(full_path, "/", PATH_MAX);
			}
			ft_strlcat(full_path, program, PATH_MAX);
			res = access(full_path, F_OK | X_OK);
			if (res == 0)
			{
				printf("File found\n");
				// execute
				return (0);
			}
			else
			{
			}
			i++;
		}
		printf("%scommand not found: %s\n", MINISHELL_PROMPT, program);
		free_ft_split(paths);
	}
}
