/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:55:32 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/15 10:53:55 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	key_is_valid(char *str);
static void	handle_invalid_key(t_exec *exec_data, int i, bool *error_happened);

void	export(t_exec *exec_data)
{
	int		i;
	bool	error_happened;

	error_happened = false;
	i = 0;
	if (!exec_data->cmd->argv[1])
		return (naked_export(exec_data->envp));
	while (exec_data->cmd->argv[++i])
	{
		if (!key_is_valid(exec_data->cmd->argv[i]))
			handle_invalid_key(exec_data, i, &error_happened);
		else if (already_in_env(exec_data->cmd->argv[i], exec_data))
			continue ;
		else
		{
			exec_data->envp = add_env(exec_data->cmd->argv[i], exec_data);
			if (!error_happened)
				g_return_value = 0;
		}
	}
}

static void	handle_invalid_key(t_exec *exec_data, int i, bool *error_happened)
{
	ft_dprintf(STDERR_FILENO,
		"minishell: export: `%s':"
		"not a valid identifier\n", exec_data->cmd->argv[i]);
	g_return_value = 1;
	*error_happened = true;
}

static bool	key_is_valid(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	i = 0;
	if (ft_isdigit(key[i]))
		return (free(key), false);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (free(key), false);
		i++;
	}
	return (free(key), true);
}

bool	check_for_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

char	**add_env(char *str, t_exec *exec_data)
{
	size_t	old_len;
	char	**new_envp;

	old_len = ft_array_length((void **) exec_data->envp);
	new_envp = ft_calloc(old_len + 2, sizeof(char *));
	if (!new_envp)
		exit_error_exec(MALLOC_ERR_CODE, MALLOC_ERR, exec_data);
	ft_memmove(new_envp, exec_data->envp, old_len * sizeof(char *));
	new_envp[old_len] = ft_strdup(str);
	free(exec_data->envp);
	return (new_envp);
}
