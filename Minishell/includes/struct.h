/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:17:21 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/11 14:56:28 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "sig.h"
//-----------------STRUCTURES-----------------//

enum e_type {
	UNDEFINED = 0,
	HERE_DOC = 1,
	PIPE = 2,
	FILE_IN = 3 ,
	FILE_OUT = 4,
	FILE_OUT_APPEND = 5,
	CMD = 6,
	BUILTIN = 7
};

enum e_builtin {
	NONE = 0,
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7
};

typedef struct s_token
{
	char			*content[2];
	enum e_type		type;
	struct s_token	*next;
}				t_token;

typedef struct s_minishell
{
	char				**envp;
	char				**secret_array;
	t_token				*token_list;
	t_sig				*sig;
}				t_minishell;

typedef struct s_here_doc
{
	int		pipe_fd[2];
	char	*delimiter;
	char	*tmp_char;
}				t_here_doc;

typedef struct s_cmd
{
	char			**argv;
	enum e_builtin	builtin;
}				t_cmd;

typedef struct s_pipe_fd
{
	int		pipe_fd[2];
}				t_pipe_fd;

typedef struct s_exec
{
	char		**envp;
	char		**secret_array;
	t_sig		*sig;
	t_token		*token_list;
	size_t		nb_cmd;
	size_t		nb_pipe;
	size_t		nb_here_doc;
	int			*here_doc_fd;
	size_t		nb_current_hd;
	t_cmd		*cmd;
	pid_t		*pid;
	int			std_save[2];
	int			pipe_fd[2];
}				t_exec;

typedef struct s_var
{
	char	*str_in;
	char	*str;
	char	**s;
	char	**spipe;
	int		nb_pipe;
	char	**env_cpy;
	int		index;
	int		i;
	char	**path;
	char	*s_p;
	char	*arg;
	char	*env;
	t_token	*new_tkn;
	bool	is_pquote;
	bool	is_squote;
	bool	quote_cmd;
	char	*quote;
	t_sig	*sig;
}				t_var;

typedef struct s_varenv
{
	int		i;
	int		j;
	int		k;
	int		m;
	int		o;
	char	*var_env;
}				t_varenv;

typedef struct s_var_quote
{
	char	*tmp;
	char	**split_tmp;
	int		i;
	int		j;
	int		k;
	char	t[2];
}				t_var_quote;

#endif
