/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:51 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/22 14:54:03 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"
//-----------------FUNCTIONS-----------------//

void	echo(char **argv);
void	cd(char **argv, t_exec *exec_data);
void	pwd(void);
void	export(t_exec *exec_data);
void	unset(char **argv, t_exec *exec_data);
void	env(char **envp);
void	exit_shell(t_exec *exec_data);

char	**add_env(char *str, t_exec *exec_data);

bool	already_in_env(char *str, t_exec *exec_data);
bool	check_for_equal(const char *str);
bool	only_key_already_in_env(char *str, t_exec *exec_data);
void	naked_export(char **envp);

#endif
