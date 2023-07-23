/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:05 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/16 21:05:48 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_return_value(char **argv, bool *is_error);

void	exit_shell(t_exec	*exec_data)
{
	pid_t	pid;
	int		return_value;
	bool	is_error;

	is_error = false;
	return_value = get_return_value(exec_data->cmd->argv, &is_error);
	if (return_value == 1 && is_error)
		return (ft_dprintf(STDERR_FILENO,
				"exit\nMinishell: exit: too many argument\n"), (void)0);
	clear_history();
	if (EASTER_EGG == 1)
	{
		pid = fork();
		if (pid == 0)
			execve(exec_data->secret_array[0],
				exec_data->secret_array, exec_data->envp);
		ft_free_array((void **)exec_data->secret_array);
	}
	return_value = get_return_value(exec_data->cmd->argv, &is_error);
	ft_free_array((void **)exec_data->envp);
	free_exec(exec_data);
	if (return_value == 2 && is_error)
		ft_dprintf(STDERR_FILENO,
			"Minishell: exit: required numerical argument\n");
	exit(return_value);
}

int	get_return_value(char **argv, bool *is_error)
{
	int	i;

	ft_dprintf(STDOUT_FILENO,
		"exit\nLa Team Rocket s'envole vers d'autres cieux!\n");
	if (!argv[1])
		return (g_return_value);
	else if (argv[1] && argv[2])
		return (*is_error = true, 1);
	else
	{
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (*is_error = true, 2);
			i++;
		}
		return (ft_atoi(argv[1]));
	}
}
