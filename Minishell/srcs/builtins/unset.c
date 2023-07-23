/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:54:20 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/22 14:54:23 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	unvalid_identifier(char *key);
void	unset_cur_argv(char *cur_argv, t_exec *exec_data);

void	unset(char **argv, t_exec *exec_data)
{
	size_t	i;

	i = 0;
	g_return_value = 0;
	while (argv[++i])
	{
		if (unvalid_identifier(argv[i]))
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: unset: `%s': not a valid identifier\n", argv[i]);
			g_return_value = 1;
			continue ;
		}
		else
			unset_cur_argv(argv[i], exec_data);
	}
}

void	unset_cur_argv(char *cur_argv, t_exec *exec_data)
{
	size_t	line_index;

	line_index = 0;
	while (exec_data->envp[line_index])
	{
		if (ft_strncmp(exec_data->envp[line_index],
				cur_argv, ft_strlen(cur_argv)) == 0)
		{
			ft_remove_array_line(
				(void **)exec_data->envp, line_index, true);
			break ;
		}
		line_index++;
	}
}

bool	unvalid_identifier(char *key)
{
	size_t	i;

	i = -1;
	while (key[++i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			continue ;
		else
			return (true);
	}
	return (false);
}
