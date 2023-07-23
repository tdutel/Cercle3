/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:51 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:30:50 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_exec *exec_data, char *old_pwd);
static char	*get_env(char *str, char **envp);
static void	go_to_oldpwd(char *path, t_exec *exec_data, char *pwd_before);
static void	go_to_home(char *path, t_exec *exec_data, char *pwd_before);

void	cd(char **argv, t_exec *exec_data)
{
	char	*path;
	char	*pwd_before;

	path = NULL;
	if (argv[1] && argv[2])
		return (g_return_value = 1, ft_dprintf(STDERR_FILENO,
				"minishell: cd: too many arguments\n"), (void)0);
	pwd_before = getcwd(NULL, 0);
	if (argv[1] == NULL)
		return (go_to_home(path, exec_data, pwd_before));
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
		return (go_to_oldpwd(path, exec_data, pwd_before));
	else
		path = argv[1];
	if (chdir(path) == -1)
		return (g_return_value = 1, ft_dprintf(
				STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno)), (void)0);
	return (g_return_value = 0, update_env(exec_data, pwd_before), (void)0);
}

static char	*get_env(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static void	update_env(t_exec *exec_data, char *old_pwd)
{
	char	*n_old_pwd;
	char	*n_pwd;
	char	*tmp;

	n_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	tmp = getcwd(NULL, 0);
	n_pwd = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!already_in_env(n_old_pwd, exec_data))
		exec_data->envp = add_env(n_old_pwd, exec_data);
	if (!already_in_env(n_pwd, exec_data))
		exec_data->envp = add_env(n_pwd, exec_data);
	free(n_old_pwd);
	free(n_pwd);
}

static void	go_to_oldpwd(char *path, t_exec *exec_data, char *pwd_before)
{
	path = get_env("OLDPWD", exec_data->envp);
	if (path == NULL)
		return (ft_dprintf(STDERR_FILENO,
				"cd: OLDPWD not set\n"), g_return_value = 1, (void) 0);
	if (chdir(&path[7]) == -1)
		return (g_return_value = 1, ft_dprintf(STDERR_FILENO, "cd: %s: %s\n",
				path, strerror(errno)), (void) 0);
	return (g_return_value = 0, update_env(exec_data, pwd_before), (void) 0);
}

static void	go_to_home(char *path, t_exec *exec_data, char *pwd_before)
{
	path = get_env("HOME", exec_data->envp);
	if (path == NULL)
		return (ft_dprintf(STDERR_FILENO,
				"cd: HOME not set\n"), g_return_value = 1, (void)0);
	if (chdir(&path[5]) == -1)
		return (g_return_value = 1, ft_dprintf(STDERR_FILENO, "cd: %s: %s\n",
				path, strerror(errno)), (void)0);
	return (g_return_value = 0, update_env(exec_data, pwd_before), (void)0);
}
