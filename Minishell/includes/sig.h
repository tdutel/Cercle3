/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:43:41 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/03 19:43:43 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include "struct.h"

typedef struct s_sig
{
	struct sigaction	*int_prompt;
	struct sigaction	*int_exec;
	struct sigaction	*int_parent;
	struct sigaction	*int_here_doc;
	struct sigaction	*quit_prompt;
	struct sigaction	*quit_exec;
	struct sigaction	*quit_parent;
}	t_sig;

void	init_sigaction(t_sig *sig);
void	sigint_prompt(int sig);
void	sig_quit_parent(int sig);
void	sigint_here_doc(int sig);

#endif
