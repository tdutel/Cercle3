/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:48:30 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/15 13:41:33 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			write_current_here_doc(t_here_doc *here_doc, size_t i);

void	write_in_here_doc(t_here_doc *here_doc, size_t nb_here_doc)
{
	size_t	i;

	i = -1;
	while (++i < nb_here_doc)
	{
		here_doc[i].tmp_char = readline(HD_PROMPT);
		if (g_return_value == 130)
			close(STDIN_FILENO);
		while (ft_strcmp(here_doc[i].tmp_char, here_doc[i].delimiter) != 0)
		{
			if (here_doc[i].tmp_char == NULL)
			{
				free(here_doc[i].tmp_char);
				ft_dprintf(2, HERE_DOC_EOF " `%s')\n", here_doc[i].delimiter);
				break ;
			}
			else
				write_current_here_doc(here_doc, i);
		}
		if (g_return_value == 130)
			break ;
		free(here_doc[i].tmp_char);
		close(here_doc[i].pipe_fd[1]);
	}
}

void	free_all_here_doc(t_here_doc *here_doc, size_t i)
{
	while (i > 0)
	{
		close(here_doc[i].pipe_fd[0]);
		close(here_doc[i].pipe_fd[1]);
		if (here_doc[i].tmp_char)
			free(here_doc[i].tmp_char);
		if (here_doc[i].delimiter)
			free(here_doc[i].delimiter);
		i--;
	}
	free(here_doc);
}

static void	write_current_here_doc(t_here_doc *here_doc, size_t i)
{
	write(here_doc[i].pipe_fd[1], here_doc[i].tmp_char,
		ft_strlen(here_doc[i].tmp_char));
	free(here_doc[i].tmp_char);
	write(here_doc[i].pipe_fd[1], "\n", 1);
	here_doc[i].tmp_char = readline(HD_PROMPT);
}
