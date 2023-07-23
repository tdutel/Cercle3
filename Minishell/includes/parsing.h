/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:44:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 13:26:38 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"
# include <stdbool.h>

//#################### FUNCTION ####################//
//-------------------- FUNCTION --------------------//
/*
*/
//#################### ENV_SYMBOL.C ####################//
int		quote_env_symbol(t_var *var, char *str_tmp, t_varenv *v_e);
int		env_symbol(t_var *var, char *str, t_varenv *v_e);
bool	catls_check(t_exec *exec_data, int i, size_t nb_cmd);
//-------------------- ENV_SYMBOL.C --------------------//
/*
*/
//#################### PARSE_PIPE.C ####################//
bool	pipe_check(char *str);
//-------------------- PARSE_PIPE.C --------------------//
/*
*/
//#################### PARSE_SYNTAX_CHECK.C ####################//
bool	newline_check(t_var *var, int i);
bool	in_check(t_var *var, int i);
bool	in2_check(t_var *var, int i);
bool	in3_check(t_var *var, int i);
bool	out_check(t_var *var, int i);
//-------------------- PARSE_SYNTAX_CHECK.C --------------------//
/*
*/
//#################### PARSE_SYNTAX_UTILS.C ####################//
bool	in_out_in(t_var var, int i);
char	last_char(char *str);
bool	out2_check(t_var *var, int i);
bool	io_check(t_var *var, int i);
//-------------------- PARSE_SYNTAX_UTILS.C --------------------//
/*
*/
//#################### PARSE_SYNTAX.C ####################//
bool	check_syntax_error(t_var *var, int i);

//-------------------- PARSE_SYNTAX.C --------------------//
/*
*/
//#################### PATH.C ####################//
char	**get_path(char **envp);
char	*process(char *str, char **path, int ind, t_var *var);
//-------------------- PATH.C --------------------//
/*
*/
//#################### QUOTES_ENV.C ####################//
void	quote_env(char *str_tmp, t_var *var, t_varenv *v_e);
//-------------------- QUOTES_ENV.C --------------------//
/*
*/
//#################### QUOTES_TYPE.C ####################//
void	dub_quote(char *str_tmp, t_var *var, t_varenv *v_e, char **tmp);
void	single_quote(char *str_tmp, t_var *var, char **tmp);
int		no_quote(t_var *var, t_varenv *v_e, t_var_quote *v_q);
//-------------------- QUOTES_TYPE.C --------------------//
/*
*/
//#################### QUOTES_UTILS.C ####################//
void	free_quote(t_var_quote *v_q);
char	*ft_reload_dup(char *str, t_var *var);
char	*ft_substrvar(char const *s, unsigned int start, size_t len, t_var var);
//-------------------- QUOTES_UTILS.c --------------------//
/*
*/
//#################### QUOTES.C ####################//
void	quote_manager(t_var *var, t_varenv *v_e);
void	quote_manager_inout(t_var *var, t_varenv *v_e);
//-------------------- QUOTES.C --------------------//
/*
*/
//#################### TOKEN_BUILTIN.C ####################//
void	token_builtin(t_var *var);
//-------------------- TOKEN_BUILTIN.C --------------------//
/*
*/
//#################### TOKEN_CHECK.C ####################//
bool	already_cmd(const t_token *t_new, const t_token *tmp);
void	token_arg(t_var *var);
int		ft_nb_pipe(char *str);
bool	is_metachar(char c);
//-------------------- TOKEN_CHECK.C --------------------//
/*
*/
//#################### TOKEN_CMD.C ####################//
void	token_cmd(t_var *var);
//-------------------- TOKEN_CMD.C --------------------//
/*
*/
//#################### TOKEN_ENV_VAR.C ####################//
void	env_arg(t_var *var, t_varenv *v_e);
//-------------------- TOKEN_ENV_VAR.C --------------------//
/*
*/
//#################### TOKEN_INFILE.C ####################//
int		token_infile(t_var *var);
//-------------------- TOKEN_INFILE.C --------------------//
/*
*/
//#################### TOKEN_INIT.C ####################//
t_token	*token_init(t_var *var);
//-------------------- TOKEN_INIT.C --------------------//
/*
*/
//#################### TOKEN_IS_IN.C ####################//
bool	is_env_in(t_var var, int j);
bool	is_env_in_str(char *str);
int		is_quote_in(char *str);
int		is_quote_between(char *str, int i);
//-------------------- TOKEN_IS_IN.C --------------------//
/*
*/
//#################### TOKEN_OUTFILE.C ####################//
int		token_outfile(t_var *var);
//-------------------- TOKEN_OUTFILE.C --------------------//
/*
*/
//#################### TOKEN_UTILS.C ####################//
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);
void	token_memcpy(t_token *dest, const t_token *src);
void	token_clear(t_token **tkn);
t_token	*token_pipe(void);
//-------------------- TOKEN_UTILS.C --------------------//
/*
*/
//#################### TOKEN.C ####################//
t_token	*get_token_list(t_var *var);
//-------------------- TOKEN.C --------------------//
/*
*/
//#################### UTILS_EXIT.C ####################//
void	exit_free(t_var *var, t_token *tkn, t_token *tkn2);
void	exit_free_secure(char **str1, char **str2);
void	exit_trunc(t_var *var);
void	exit_sig(void);
//-------------------- UTILS_EXIT.C --------------------//
/*
*/
//#################### UTILS_FREE.C ####################//
void	ft_free_secure(char **elem);
void	ft_free_split_secure(char ***splitted_element);
void	free_var(t_var *var);
void	ft_free_sig(t_sig **sig);
//-------------------- UTILS_FREE.C --------------------//
/*
*/
//#################### UTILS_STR.C ####################//
char	*ft_strjoinsp(char *s1, char *s2, int n);
char	*ft_strjoinsp2(char *s1, char *s2, int n, t_var_quote *v_q);
//-------------------- UTILS_STR.C --------------------//
/*
*/
//#################### UTILS_TRUNC.C ####################//
char	*ft_trunc(char *str, int start, char *c, t_var var);
//-------------------- UTILS_TRUNC.C --------------------//
/*
*/
//#################### UTILS.C ####################//
bool	var_init(t_var *var);
bool	is_builtin(char *str);
bool	has_in_out(char **s, int j);
char	*check_var(t_var *var, t_varenv *v_e);
char	*ft_free_process(char **to_free, char *to_return);
//-------------------- UTILS.C --------------------//
/*
*/
//#################### UTILS2.C ####################//
char	*ft_space_str(t_var *var);
//-------------------- UTILS2.C --------------------//

#endif
