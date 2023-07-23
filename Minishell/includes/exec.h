/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:57:11 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/03 12:49:20 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
# define HD_PROMPT "heredoc> "

//-----------------FUNCTION-----------------//

//########### EXECUTION.C ###########//
void	master_exec(t_minishell *minishell_data);
void	free_exec(t_exec *exec_data);
void	free_exec_child(t_exec *exec_data);
void	cmd_loop(t_exec *exec_data, size_t current_cmd);
void	exec_multiple_cmd(t_exec *exec_data);
void	exit_error_exec(int error_code, char *error_msg, t_exec *to_free);

//########### HERE_DOC.C ###########//
int		*get_here_doc_fd(t_token *token_list, t_exec *exec_data);
void	write_in_here_doc(t_here_doc *here_doc, size_t nb_here_doc);
void	free_all_here_doc(t_here_doc *here_doc, size_t i);

//########### TRANSLATE.C ###########//
t_cmd	*get_cmd_data(t_exec *exec_data);

//########### EXEC_CMD.C ###########//
void	exec_piped_cmd(t_exec *exec_data, size_t current_cmd);
void	handle_io(t_exec *exec_data, size_t current_cmd);
void	exec_builtin(t_exec *exec_data, size_t current_cmd);

#endif
