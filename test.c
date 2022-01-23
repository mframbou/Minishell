/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 18-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 23-01-2022 18:47 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#define _GNU_SOURCE 1
#include "includes/libft.h"
#include <stdio.h>





void	remove_char_from_string(char **str, int index)
{
	char	*res;
	int		new_len;
	char	old_char;

	if (index > ft_strlen(*str) - 1 || index < 0)
		return ;
	new_len = ft_strlen(*str) - 1;
	res = malloc(sizeof(char) * (new_len + 1));
	if (res)
	{
		ft_bzero(res, new_len + 1);
		old_char = (*str)[index];
		(*str)[index] = '\0';
		ft_strlcat(res, *str, new_len + 1);
		(*str)[index] = old_char;
		ft_strlcat(res, &((*str)[index + 1]), new_len + 1);
		free(*str);
		*str = res;
	}
}

/*
	As remove_char_from_string but for a whole substring (between start and end)
*/
void	remove_substr_from_string(char **str, int start, int end)
{
	while (--end >= start)
		remove_char_from_string(str, start);
}

int	is_closed_quote(char *str)
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
			if (curr_file->d_type == DT_REG)
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

	files = malloc(sizeof(char *) * (count_files_in_directory(".") + 1));
	i = 0;
	dir = opendir(".");
	if (dir)
	{
		curr_file = readdir(dir);
		while (curr_file)
		{
			if (curr_file->d_type == DT_REG)
				files[i++] = ft_strdup(curr_file->d_name);
			curr_file = readdir(dir);
		}
		files[i] = NULL;
		closedir(dir);
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

static void	add_quotes_to_strs(char **array)
{
	int		i;
	char	*str;
	int		new_str_size;

	i = 0;
	while (array[i])
	{
		new_str_size = ft_strlen(array[i]) + 3;
		str = malloc(sizeof(char) * new_str_size);
		str[0] = '\'';
		ft_strlcpy(&(str[1]), str, new_str_size);
		str[new_str_size - 2] = '\'';
		str[new_str_size - 1] = '\0';
		free(array[i]);
		array[i] = str;
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
char	**generate_wildcard_in_current_dir(void)
{
	char			**files;
	
	if (count_files_in_directory(".") == 0)
	{
		files = malloc(sizeof(char *) * 2); // ["*", NULL]
		files[0] = ft_strdup("'*'");
		files[1] = NULL;
	}
	else
		files = list_files_in_directory(".");
	sort_string_array(files);
	add_quotes_to_strs(files);
	return (files);
}

/*
	i = str array index
	j = result index
	k = current str in array index

	Add a space after each string (except for last, so remove 1 at the end)
	Which "counters" the + 1 for the '\0'
*/
char	*convert_str_array_to_one_line(char **array)
{
	int		total_len;
	int		i;
	int		j;
	int		k;
	char	*res;

	total_len = 0;
	i = 0;
	while (array[i])
		total_len += ft_strlen(array[i++]) + 1;
	res = malloc(sizeof(char) * (total_len));
	if (res)
	{
		i = 0;
		j = 0;
		while (array[i])
		{
			k = 0;
			while (array[i][k])
				res[j++] = array[i][k++];
			if (array[i + 1])
				res[j++] = ' ';
			i++;
		}
		res[j] = 0;
	}
	return (res);
}

/*
	Inserts str into src at index index.

	"Test chad", "giga ", 5 => "Test giga chad"

	i = res index
	j = src index
*/
static char	*insert_str_in_str(char *src, char *str, int index)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	res = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(str) + 1));
	if (index < 0 || index > ft_strlen(src))
		return (NULL);
	if (res)
	{
		i = 0;
		j = 0;
		k = 0;
		while (src[j] && j < index)
			res[i++] = src[j++];
		while (str[k])
			res[i++] = str[k++];
		while (src[j])
			res[i++] = src[j++];
		res[i] = '\0';
	}
	free(src);
	free(str);
	return (res);
}

/*
	Takes pointer to line ("echo * > test.txt")
	- Interpret wildcard : "echo foo.bar pouet.txt oronda.bg > test.txt"

	If we find a quote skip it, otherwise if we find a * interpret it

	If we have multiple wildcards next to each other, only count 1
	eg. "echo *********" == "echo *"
*/
void	interpret_wildcards(char **line)
{
	int		i;
	char	**files;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += is_closed_quote(&((*line)[i]));
		if ((*line)[i] == '*')
		{
			int star_start = i;
			while ((*line)[i] == '*')
				i++;
			int star_end = i;
			files = generate_wildcard_in_current_dir();
			char *files_one_line = convert_str_array_to_one_line(files);
			free_ft_split(files);
			remove_substr_from_string(line, star_start, star_end);
			*line = insert_str_in_str(*line, files_one_line, star_start);
			continue ;
		}
		i++;
	}
}
