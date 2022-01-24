/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 18-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 19:53 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_files_in_directory(char *folder)
{
	int				count;
	DIR				*dir;
	struct dirent	*curr_file;

	count = 0;
	dir = opendir(folder);
	if (dir)
	{
		curr_file = readdir(dir);
		while (curr_file)
		{
			if (curr_file->d_type == DT_REG && curr_file->d_name[0] != '.')
				count++;
			curr_file = readdir(dir);
		}
		closedir(dir);
	}
	return (count);
}

static char	**list_files_in_directory(char *folder)
{
	char			**files;
	DIR				*dir;
	struct dirent	*curr_file;
	int				i;

	files = ft_malloc(sizeof(char *) * (count_files_in_directory(".") + 1));
	i = 0;
	dir = opendir(".");
	if (dir)
	{
		curr_file = readdir(dir);
		while (curr_file)
		{
			if (curr_file->d_type == DT_REG && curr_file->d_name[0] != '.')
				files[i++] = ft_strdup(curr_file->d_name);
			curr_file = readdir(dir);
		}
		files[i] = NULL;
		closedir(dir);
	}
	return (files);
}

/*
	Add quotes so files like "test 1.txt" are not splitted while parsing
*/
static void	add_quotes_to_strs(char **array)
{
	int		i;
	int		j;
	char	*str;
	int		new_str_size;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '\'')
				array[i][j] = '`';
			j++;
		}
		new_str_size = ft_strlen(array[i]) + 3;
		str = ft_malloc(sizeof(char) * new_str_size);
		str[0] = '\'';
		ft_strlcpy(&(str[1]), array[i], new_str_size);
		str[new_str_size - 2] = '\'';
		str[new_str_size - 1] = '\0';
		ft_free(array[i]);
		array[i] = str;
		i++;
	}
}

/*
	- Wildcard (*) list all files (only FILES) in the current directory
	- Wildcard is alphabetically sorted
	https://www.gnu.org/software/bash/manual/html_node/Filename-Expansion.html

	In bash and Bourne-like shells in general (zsh being the exception),
	globs like * that match no file expand to themselves

	"echo *" in an empty folder will output "*"

	If no files, just as bash set the * character literally
	so out string array looks like this: ["*", NULL]
*/
char	**generate_wildcard_in_current_dir(void)
{
	char			**files;

	if (count_files_in_directory(".") == 0)
	{
		files = ft_malloc(sizeof(char *) * 2);
		files[0] = ft_strdup("'*'");
		files[1] = NULL;
	}
	else
		files = list_files_in_directory(".");
	sort_string_array(files);
	add_quotes_to_strs(files);
	return (files);
}

char	*get_one_line_wildcard(void)
{
	char	**files;
	char	*line;

	files = generate_wildcard_in_current_dir();
	if (files)
	{
		line = convert_str_array_to_one_line(files);
		free_ft_split(files);
	}
	return (line);
}
