/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:21:08 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/15 00:38:40 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_piped_cmd(t_exec *exec_data, size_t current_cmd)
{
	handle_io(exec_data, current_cmd);
	if (exec_data->cmd[current_cmd].builtin != NONE)
	{
		exec_builtin(exec_data, current_cmd);
		free_exec_child(exec_data);
		exit(EXIT_SUCCESS);
	}
	execve(exec_data->cmd[current_cmd].argv[0],
		exec_data->cmd[current_cmd].argv, exec_data->envp);
	ft_dprintf(STDERR_FILENO, "Minishell: %s: %s\n",
		exec_data->cmd[current_cmd].argv[0], strerror(errno));
	ft_free_array((void **)exec_data->secret_array);
	free_exec_child(exec_data);
}

void	exec_builtin(t_exec *exec_data, size_t current_cmd)
{
	handle_io(exec_data, current_cmd);
	if (exec_data->cmd[current_cmd].builtin == ECHO)
		echo(exec_data->cmd[current_cmd].argv);
	else if (exec_data->cmd[current_cmd].builtin == CD)
		cd(exec_data->cmd[current_cmd].argv, exec_data);
	else if (exec_data->cmd[current_cmd].builtin == PWD)
		pwd();
	else if (exec_data->cmd[current_cmd].builtin == EXPORT)
		export(exec_data);
	else if (exec_data->cmd[current_cmd].builtin == UNSET)
		unset(exec_data->cmd[current_cmd].argv, exec_data);
	else if (exec_data->cmd[current_cmd].builtin == ENV)
		env(exec_data->envp);
	else if (exec_data->cmd[current_cmd].builtin == EXIT)
		exit_shell(exec_data);
	if (g_return_value == MALLOC_ERR_CODE)
		exit_error_exec(MALLOC_ERR_CODE, MALLOC_ERR, exec_data);
}
