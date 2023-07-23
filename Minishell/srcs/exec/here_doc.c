/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:06:42 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/02 14:33:59 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: expand env var in here_doc
static t_here_doc	*fill_hd_data(t_token *token_list, size_t nb_here_doc);
static size_t		count_here_doc(t_token *token_list);
static int			*turn_pipe_in_fd(t_here_doc *here_doc, size_t nb_here_doc);

int	*get_here_doc_fd(t_token *token_list, t_exec *exec_data)
{
	t_token		*tmp;
	t_here_doc	*here_doc;
	int			*here_doc_fd;

	sigaction(SIGINT, exec_data->sig->int_here_doc, NULL);
	g_return_value = 0;
	tmp = token_list;
	exec_data->nb_here_doc = count_here_doc(tmp);
	if (exec_data->nb_here_doc == 0)
		return (NULL);
	here_doc = fill_hd_data(token_list, exec_data->nb_here_doc);
	if (here_doc == NULL)
		return (NULL);
	here_doc_fd = turn_pipe_in_fd(here_doc, exec_data->nb_here_doc);
	free(here_doc);
	return (here_doc_fd);
}

static size_t	count_here_doc(t_token *token_list)
{
	size_t	nb_here_doc;

	nb_here_doc = 0;
	while (token_list)
	{
		if (token_list->type == HERE_DOC)
			nb_here_doc++;
		token_list = token_list->next;
	}
	return (nb_here_doc);
}

static int	*turn_pipe_in_fd(t_here_doc *here_doc, size_t nb_here_doc)
{
	size_t	i;
	int		*here_doc_fd;

	i = -1;
	here_doc_fd = ft_calloc(nb_here_doc, sizeof(int));
	while (++i < nb_here_doc)
	{
		here_doc_fd[i] = dup(here_doc[i].pipe_fd[0]);
		close(here_doc[i].pipe_fd[0]);
	}
	return (here_doc_fd);
}

static t_here_doc	*fill_hd_data(t_token *token_list, size_t nb_here_doc)
{
	t_here_doc	*here_doc;
	t_token		*tmp;
	size_t		i;

	here_doc = ft_calloc(nb_here_doc, sizeof(t_here_doc));
	if (!here_doc)
		return (g_return_value = MALLOC_ERR_CODE, NULL);
	tmp = token_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			here_doc[i].delimiter = tmp->content[0];
			if (pipe(here_doc[i].pipe_fd) == -1)
				return (free_all_here_doc(here_doc, i),
					g_return_value = PIPE_FAIL_CODE, NULL);
			i++;
		}
		tmp = tmp->next;
	}
	write_in_here_doc(here_doc, nb_here_doc);
	if (g_return_value == 130)
		return (free(here_doc), NULL);
	return (here_doc);
}
