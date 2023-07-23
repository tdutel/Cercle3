/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:43:36 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/03 19:43:38 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_prompt(int sig)
{
	(void)sig;
	ft_dprintf(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_return_value = 130;
}

void	sigint_here_doc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	ft_dprintf(STDOUT_FILENO, "\n");
	g_return_value = 130;
}

void	sig_quit_parent(int sig)
{
	(void)sig;
	ft_dprintf(STDOUT_FILENO, "Quit (core dumped)\n");
	g_return_value = 131;
}
