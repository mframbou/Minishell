/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:59:30 by mframbou          #+#    #+#             */
/*   Updated: 2022/01/10 11:26:02 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// Builtins
void	echo_command(char *argv[], int output_fd);
void	unset_command(char *argv[], int output_fd);
void	env_command(char *argv[], int output_fd);
void	export_command(char *argv[], int output_fd);
void	pwd_command(char *argv[], int output_fd);
void	cd_command(char *argv[], int output_fd);
void	exit_command(char *argv[], int output_fd);

#endif