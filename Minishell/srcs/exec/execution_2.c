/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:33:12 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/12 16:33:14 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			exec_last_cmd(t_exec *exec_data, size_t current_cmd);

void	exec_multiple_cmd(t_exec *exec_data)
{
	size_t	current_cmd;
	int		status;

	current_cmd = 0;
	while (current_cmd < exec_data->nb_cmd - 1)
		cmd_loop(exec_data, current_cmd++);
	exec_last_cmd(exec_data, current_cmd);
	current_cmd = -1;
	while (++current_cmd < exec_data->nb_cmd)
	{
		waitpid(exec_data->pid[current_cmd], &status, 0);
		if (WIFEXITED(status))
			g_return_value = WEXITSTATUS(status);
	}
}

void	cmd_loop(t_exec *exec_data, size_t current_cmd)
{
	pipe(exec_data->pipe_fd);
	exec_data->pid[current_cmd] = fork();
	if (exec_data->pid[current_cmd] == -1)
		return (g_return_value = 1,
			perror("minishell"), free_exec(exec_data), (void)0);
	if (exec_data->pid[current_cmd] == 0)
	{
		sigaction(SIGINT, exec_data->sig->int_exec, NULL);
		dup2(exec_data->pipe_fd[1], STDOUT_FILENO);
		close(exec_data->pipe_fd[0]);
		close(exec_data->pipe_fd[1]);
		exec_piped_cmd(exec_data, current_cmd);
	}
	sigaction(SIGINT, exec_data->sig->int_parent, NULL);
	dup2(exec_data->pipe_fd[0], STDIN_FILENO);
	close(exec_data->pipe_fd[0]);
	close(exec_data->pipe_fd[1]);
}

void	exit_error_exec(int error_code, char *error_msg, t_exec *to_free)
{
	g_return_value = error_code;
	ft_dprintf(STDERR_FILENO, error_msg);
	free_exec(to_free);
}

static void	exec_last_cmd(t_exec *exec_data, size_t current_cmd)
{
	exec_data->pid[current_cmd] = fork();
	if (exec_data->pid[current_cmd] == -1)
	{
		free_exec(exec_data);
		exit(EXIT_FAILURE);
	}
	if (exec_data->pid[current_cmd] != 0)
		return ;
	handle_io(exec_data, current_cmd);
	if (exec_data->cmd[current_cmd].builtin != NONE)
	{
		exec_builtin(exec_data, current_cmd);
		free_exec(exec_data);
		exit(EXIT_SUCCESS);
	}
	execve(exec_data->cmd[current_cmd].argv[0],
		exec_data->cmd[current_cmd].argv, exec_data->envp);
	ft_dprintf(STDERR_FILENO, "Minishell: %s: %s\n",
		exec_data->cmd[current_cmd].argv[0], strerror(errno));
	ft_free_array((void **)exec_data->secret_array);
	free_exec_child(exec_data);
	exit(EXIT_FAILURE);
}
