/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:53:45 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/15 13:26:59 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec	*get_exec_data(t_minishell *minishell);
static size_t	get_nb_cmd(t_token *token_list);
static void		copy_minishell_data(t_minishell *minishell, t_exec *exec_data);

void	master_exec(t_minishell	*minishell)
{
	t_exec	*exec_data;

	exec_data = get_exec_data(minishell);
	if (g_return_value == 130)
		return (dup2(exec_data->std_save[0], STDIN_FILENO),
			dup2(exec_data->std_save[1], STDOUT_FILENO), free_exec(exec_data));
	if (g_return_value == GET_EXEC_FAIL_CODE)
		return (exit_error_exec(GET_EXEC_FAIL_CODE,
				GET_EXEC_FAIL "\n", exec_data));
	sigaction(SIGQUIT, exec_data->sig->quit_parent, NULL);
	if (catls_check(exec_data, 0, exec_data->nb_cmd))
		return (free_exec(exec_data));
	if (exec_data->nb_cmd == 1 && exec_data->cmd[0].builtin)
		exec_builtin(exec_data, 0);
	else if (exec_data->nb_cmd == 0)
		handle_io(exec_data, 0);
	else if (exec_data->nb_cmd != 0)
		exec_multiple_cmd(exec_data);
	dup2(exec_data->std_save[0], STDIN_FILENO);
	dup2(exec_data->std_save[1], STDOUT_FILENO);
	minishell->envp = exec_data->envp;
	free_exec(exec_data);
}

static t_exec	*get_exec_data(t_minishell *minishell)
{
	t_exec	*exec_data;
	size_t	i;

	exec_data = ft_calloc(1, sizeof(t_exec));
	if (!exec_data)
		return (NULL);
	copy_minishell_data(minishell, exec_data);
	if (exec_data->std_save[0] == -1 || exec_data->std_save[1] == -1)
		return (g_return_value = GET_EXEC_FAIL_CODE, exec_data);
	exec_data->nb_cmd = get_nb_cmd(minishell->token_list);
	exec_data->nb_pipe = exec_data->nb_cmd - 1;
	exec_data->here_doc_fd = get_here_doc_fd(minishell->token_list, exec_data);
	if (exec_data->here_doc_fd == NULL && g_return_value != 0)
		return (exec_data);
	exec_data->cmd = get_cmd_data(exec_data);
	if (exec_data->cmd == NULL)
		return (g_return_value = GET_EXEC_FAIL_CODE, exec_data);
	exec_data->pid = malloc(sizeof(pid_t) * exec_data->nb_cmd);
	if (!exec_data->pid)
		return (g_return_value = GET_EXEC_FAIL_CODE, exec_data);
	i = -1;
	while (++i < exec_data->nb_cmd)
		exec_data->pid[i] = -1;
	return (exec_data);
}

static void	copy_minishell_data(t_minishell *minishell, t_exec *exec_data)
{
	exec_data->sig = minishell->sig;
	exec_data->secret_array = minishell->secret_array;
	exec_data->token_list = minishell->token_list;
	exec_data->envp = minishell->envp;
	exec_data->std_save[0] = dup(STDIN_FILENO);
	exec_data->std_save[1] = dup(STDOUT_FILENO);
}

static size_t	get_nb_cmd(t_token *token_list)
{
	size_t	nb_cmd;

	nb_cmd = 0;
	while (token_list)
	{
		if (token_list->type == CMD || token_list->type == BUILTIN)
			nb_cmd++;
		token_list = token_list->next;
	}
	return (nb_cmd);
}
