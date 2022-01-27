/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 12-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 27-01-2022 12:50 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../../../includes/minishell.h"

typedef struct s_dic_variable
{
	char	*key;
	char	*value;
}	t_env_variable;

typedef struct s_env_link
{
	t_env_variable		var;
	struct s_env_link	*next;
}	t_env_link;

void	add_env_variable(char *key, char *value);
void	remove_env_variable(char *key);
void	free_var_list(void);
char	*get_env_variable(char *key);
char	**get_env_as_string_array(void);

#endif