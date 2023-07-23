/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:54:12 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/22 14:54:13 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	naked_export(char **envp)
{
	int		i;
	char	**sorted_envp;
	char	*tmp;

	i = 0;
	sorted_envp = (char **)ft_array_dup((void **)envp, false, true);
	if (!sorted_envp)
		return (g_return_value = MALLOC_ERR_CODE, (void)0);
	i = -1;
	ft_sort_array(sorted_envp);
	while (sorted_envp[++i])
	{
		tmp = ft_strchr(sorted_envp[i], '=');
		if (!tmp)
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", sorted_envp[i]);
		else
		{
			*tmp = '\0';
			ft_dprintf(STDOUT_FILENO,
				"declare -x %s=\"%s\"\n", sorted_envp[i], tmp + 1);
			*tmp = '=';
		}
	}
	ft_free_array((void **)sorted_envp);
	g_return_value = 0;
}

bool	already_in_env(char *str, t_exec *exec_data)
{
	int		i;
	int		len_until_equal;
	bool	have_equal;

	have_equal = check_for_equal(str);
	if (!have_equal)
		return (only_key_already_in_env(str, exec_data));
	i = 0;
	len_until_equal = 0;
	while (str[len_until_equal] && str[len_until_equal] != '=')
		len_until_equal++;
	while (exec_data->envp[i])
	{
		if (ft_strncmp(str, exec_data->envp[i], len_until_equal) == 0)
		{
			free(exec_data->envp[i]);
			exec_data->envp[i] = ft_strdup(str);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	only_key_already_in_env(char *str, t_exec *exec_data)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(str);
	i = -1;
	while (exec_data->envp[++i])
	{
		if (ft_strncmp(str, exec_data->envp[i], key_len) == 0)
			return (true);
	}
	return (false);
}
