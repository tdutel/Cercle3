/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:55:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/11 14:55:08 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H

//#################### HERE-DOC RELATED ####################//
# define HERE_DOC_EOF "minishell: warning: \
here-document delimited by end-of-file (wanted "

//#################### SYNTAX RELATED ####################//
# define NL_SYNTAX_ERR "minishell: syntax error near unexpected token `newline'"
# define PIPE_SYNTAX_ERR "minishell: syntax error near unexpected token `|'"
# define PIPE2_SYNTAX_ERR "minishell: syntax error near unexpected token `||'"
# define IN_SYNTAX_ERR "minishell: syntax error near unexpected token `<'"
# define IN2_SYNTAX_ERR "minishell: syntax error near unexpected token `<<'"
# define OUT_SYNTAX_ERR "minishell: syntax error near unexpected token `>'"
# define OUT2_SYNTAX_ERR "minishell: syntax error near unexpected token `>>'"
# define IN3_SYNTAX_ERR "minishell: syntax error near unexpected token `<<<'"
# define IO_SYNTAX_ERR "minishell: syntax error near unexpected token `<>'"

//#################### FUNCTION CALL RELATED ####################//
# define CALLOC_FAIL_CODE 12
# define CALLOC_FAIL "minishell: calloc failed in function: "
# define DUP_FAIL_CODE 13
# define DUP_FAIL "minishell: dup failed in function: "
# define FORK_FAIL_CODE 127
# define FORK_FAIL "minishell: fork failed in function: "
# define PIPE_FAIL_CODE 126
# define PIPE_FAIL "minishell: pipe failed in function: "
# define GET_EXEC_FAIL_CODE 42
# define GET_EXEC_FAIL "minishell: error getting exec data."

//#################### MEMORY RELATED ####################//
# define MALLOC_ERR_CODE 12
# define MALLOC_ERR "minishell: malloc error in function: "
#endif
