/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 25-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 27-01-2022 13:09 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	perror_return(char *str)
{
	perror(str);
	return (-2);
}

/*
	If file doesn't exists / is not a regular file or a symlink, we don't
	consider it as executable

	stat function directly use the file pointed by the symlink if any,
	so we don't need to check if it is a symlink, then if the file it points
	to is a regular file

	Macros S_ISREG and S_ISLNK help doing it instead of doing binary operations
	S_IXUSR = permission bit for execution
*/
int	is_regular_file_or_symlink(char *file)
{
	struct stat	file_infos;
	int			stat_return;

	stat_return = stat(file, &file_infos);
	if (stat_return == -1 \
	|| !S_ISREG(file_infos.st_mode) \
	|| !(S_IEXEC & file_infos.st_mode))
	{
		return (0);
	}
	return (1);
}

/*
	https://pubs.opengroup.org/onlinepubs/9699919799/utilities/
	V3_chap02.html#tag_18_09_01_01

	If the command name contains at least one <slash>, the shell shall execute 
	the utility in a separate utility environment with actions equivalent 
	to calling the execl() function

	If we have a '/' in the filename, then execute it as absolute / relative
		path. But if there isn't any slashes, just search in PATH

	S_IFMT = Bit mask for file type, used to only keep the file types of
		stat.st_mode structure
	If file is different from symlink or regular file, dont execute it
*/
char	*search_absolute_path_program(char *program)
{
	char		*res;
	struct stat	file_infos;

	if (!is_regular_file_or_symlink(program) || !has_slash(program))
	{
		perror(program);
		return (NULL);
	}
	return (ft_strdup(program));
}
