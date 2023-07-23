/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:43:33 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/11 15:01:24 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_malloc(t_sig *sig);
static void	init_int(t_sig *sig);
static void	init_quit(t_sig *sig);

void	init_sigaction(t_sig *sig)
{
	sig->int_prompt = ft_calloc(1, sizeof(struct sigaction));
	sig->int_exec = ft_calloc(1, sizeof(struct sigaction));
	sig->int_parent = ft_calloc(1, sizeof(struct sigaction));
	sig->int_here_doc = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_prompt = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_exec = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_parent = ft_calloc(1, sizeof(struct sigaction));
	check_malloc(sig);
	init_int(sig);
	init_quit(sig);
}

static void	init_int(t_sig *sig)
{
	sig->int_prompt->sa_handler = sigint_prompt;
	sig->int_prompt->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_prompt->sa_mask);
	sig->int_parent->sa_handler = SIG_IGN;
	sig->int_parent->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_parent->sa_mask);
	sig->int_exec->sa_handler = SIG_DFL;
	sig->int_exec->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_exec->sa_mask);
	sig->int_here_doc->sa_handler = sigint_here_doc;
	sig->int_here_doc->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_here_doc->sa_mask);
}

static void	init_quit(t_sig *sig)
{
	sig->quit_prompt->sa_handler = SIG_IGN;
	sig->quit_prompt->sa_flags = SA_RESTART;
	sigemptyset(&sig->quit_prompt->sa_mask);
	sig->quit_parent->sa_handler = sig_quit_parent;
	sig->quit_parent->sa_flags = SA_RESTART;
	sigemptyset(&sig->quit_parent->sa_mask);
}

static void	check_malloc(t_sig *sig)
{
	if (!sig->int_prompt || !sig->int_exec
		|| !sig->quit_prompt || !sig->quit_exec
		|| !sig->int_parent || !sig->quit_parent
		|| !sig->int_here_doc)
	{
		ft_dprintf(STDERR_FILENO, MALLOC_ERR "init_sigaction\n");
		if (sig->int_prompt)
			free(sig->int_prompt);
		if (sig->int_exec)
			free(sig->int_exec);
		if (sig->quit_prompt)
			free(sig->quit_prompt);
		if (sig->quit_exec)
			free(sig->quit_exec);
		if (sig->int_parent)
			free(sig->int_parent);
		if (sig->quit_parent)
			free(sig->quit_parent);
		if (sig->int_here_doc)
			free(sig->int_here_doc);
		exit(EXIT_FAILURE);
	}
}
