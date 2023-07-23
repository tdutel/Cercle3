/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:46:30 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/14 07:46:33 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_in_fd(t_token *token, t_exec *exec_data);
static int	get_out_fd(t_token *token);
static void	io_redirect(t_token *tmp, t_exec *exec_data);

void	handle_io(t_exec *exec_data, size_t current_cmd)
{
	size_t	i;
	t_token	*tmp;

	i = 0;
	tmp = exec_data->token_list;
	while (tmp && i < current_cmd)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	io_redirect(tmp, exec_data);
}

static void	io_redirect(t_token *tmp, t_exec *exec_data)
{
	int	fd[2];

	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == FILE_IN || tmp->type == HERE_DOC)
		{
			fd[0] = get_in_fd(tmp, exec_data);
			if (fd[0] == -1)
				return (g_return_value = 42, (void)0);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		else if (tmp->type == FILE_OUT || tmp->type == FILE_OUT_APPEND)
		{
			fd[1] = get_out_fd(tmp);
			if (fd[1] == -1)
				return (free_exec(exec_data), exit(g_return_value = 42));
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		tmp = tmp->next;
	}
}

static int	get_in_fd(t_token *token, t_exec *exec_data)
{
	int	fd;

	if (token->type == FILE_IN)
		fd = open(token->content[0], O_RDONLY);
	else if (token->type == HERE_DOC)
		fd = exec_data->here_doc_fd[exec_data->nb_current_hd++];
	else
		fd = -1;
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: %s: %s\n",
			strerror(errno), token->content[0]);
	}
	return (fd);
}

static int	get_out_fd(t_token *token)
{
	int	fd;

	if (token->type == FILE_OUT)
		fd = open(token->content[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == FILE_OUT_APPEND)
		fd = open(token->content[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: %s: %s\n",
			strerror(errno), token->content[0]);
		return (-1);
	}
	return (fd);
}
