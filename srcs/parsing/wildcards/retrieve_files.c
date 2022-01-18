/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 18-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 18-01-2022 22:11 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
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
	}
	return (count);
}

static char	**list_files_in_directory(char *folder)
{
	char			**files;
	DIR				*dir;
	struct dirent	*curr_file;
	int				i;

	files = malloc(sizeof(char *) * (count_files_in_directory(".") + 1));
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
	}
	return (files);
}

/*
	Compares first string with every other, second with every other (except 1st)
	and so on
*/
static void	sort_string_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0) // If first string is bigger, put it after (swap)
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
			j++;
		}
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
*/
static char	**generate_wildcard_in_current_dir(void)
{
	char			**files;
	
	if (count_files_in_directory(".") == 0)
	{
		files = malloc(sizeof(char *) * 2); // ["*", NULL]
		files[0] = ft_strdup("*");
		files[1] = NULL;
	}
	else
		files = list_files_in_directory(".");
	sort_string_array(files);
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
