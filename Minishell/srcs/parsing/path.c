/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:19:20 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 09:42:05 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	path_in_env(char **envp);

char	**get_path(char **envp)
{
	int		i;
	char	**split_path;
	char	*path;

	i = 0;
	if (!path_in_env(envp))
		return (NULL);
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	split_path = ft_split(path, ':');
	ft_free_secure(&path);
	return (split_path);
}

static char	**path_arg_cat(char **src, char *root_arg, t_var *var)
{
	int		i;
	char	**pathsrc;

	pathsrc = malloc(sizeof(char *) * (ft_array_length((void **)src) + 1));
	if (!pathsrc)
		exit_free(var, NULL, NULL);
	i = 0;
	while (src[i])
	{
		pathsrc[i] = ft_strjoin(src[i], root_arg);
		i++;
	}
	pathsrc[i] = NULL;
	return (pathsrc);
}

char	*process(char *str, char **path, int ind, t_var *var)
{
	char	**path_cmb;
	int		i;
	char	**split_argv;
	char	*root_arg;

	split_argv = ft_split(str, ' ');
	if (path_in_env(var->env_cpy) == false)
		return (root_arg = ft_strdup(split_argv[ind]),
			ft_free_split(split_argv), root_arg);
	root_arg = ft_strjoin("/", split_argv[ind]);
	path_cmb = path_arg_cat(path, root_arg, var);
	ft_free_secure(&root_arg);
	i = 0;
	while (path_cmb[i] && access(path_cmb[i], X_OK) == -1)
		i++;
	if (!path_cmb[i])
		return (root_arg = ft_strdup(split_argv[ind]),
			ft_free_split_secure(&split_argv),
			ft_free_split_secure(&path), ft_free_array((void *)path_cmb),
			root_arg);
	root_arg = ft_strdup(path_cmb[i]);
	ft_free_split_secure(&split_argv);
	ft_free_split_secure(&path);
	ft_free_array((void *)path_cmb);
	return (root_arg);
}

static bool	path_in_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			return (true);
		i++;
	}
	return (false);
}
