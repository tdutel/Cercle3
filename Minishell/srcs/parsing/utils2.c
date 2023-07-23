/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:23:51 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 10:29:46 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_str_bis(t_var *var, t_var_quote *v_q, char **new);

static void	fill_str_quote(char *str, int *start, t_var_quote *v_q, t_var *var)
{
	if (str[*start] == '|')
	{
		v_q->tmp[v_q->j] = '`';
		var->is_pquote = true;
	}
	else if (str[*start] == ' ')
	{
		v_q->tmp[v_q->j] = '~';
		var->is_squote = true;
	}
	else
		v_q->tmp[v_q->j] = str[*start];
	v_q->j++;
	*start = *start + 1;
}

static char	*ft_quote_str(t_var_quote *v_q, char c, t_var *var, char **new)
{
	t_var_quote	v_q2;

	v_q2.i = 1;
	v_q2.j = 0;
	while (v_q->tmp[v_q->i + v_q2.i] != c && v_q->tmp[v_q->i + v_q2.i])
	{
		v_q2.i++;
	}
	v_q2.i++;
	v_q2.tmp = malloc(sizeof(char) * (v_q2.i + 3));
	if (!v_q2.tmp)
	{
		ft_free_secure(new);
		ft_free_secure(&v_q->tmp);
		exit(EXIT_FAILURE);
	}
	v_q2.tmp[v_q2.j++] = '\\';
	while (v_q2.j < v_q2.i + 1)
	{
		fill_str_quote(v_q->tmp, &v_q->i, &v_q2, var);
	}
	v_q->i = v_q->i - 1;
	v_q2.tmp[v_q2.j] = '\\';
	v_q2.tmp[v_q2.j + 1] = '\0';
	return (v_q2.tmp);
}

static void	fill_str(t_var *var, t_var_quote *v_q, char **new)
{
	v_q->t[0] = v_q->tmp[v_q->i];
	if (v_q->tmp[v_q->i] == '\'' || v_q->tmp[v_q->i] == '"')
		fill_str_bis(var, v_q, new);
	else if (v_q->tmp[v_q->i] == '|')
	{
		*new = ft_strjoinsp2(*new, " | ", 0, v_q);
		var->nb_pipe++;
	}
	else if (v_q->tmp[v_q->i] == '<' && v_q->i > 0
		&& v_q->tmp[v_q->i - 1] != '<')
		*new = ft_strjoinsp2(*new, " <", 0, v_q);
	else if (v_q->i > 0
		&& v_q->tmp[v_q->i] == '>' && v_q->tmp[v_q->i - 1] != '>')
		*new = ft_strjoinsp2(*new, " >", 0, v_q);
	else
		*new = ft_strjoinsp2(*new, v_q->t, 0, v_q);
}

static void	fill_str_bis(t_var *var, t_var_quote *v_q, char **new)
{
	char	*tmp;

	if (v_q->tmp[v_q->i] == '\'')
	{
		tmp = ft_quote_str(v_q, '\'', var, new);
		*new = ft_strjoinsp2(*new, tmp, 0, v_q);
		if (tmp)
			free(tmp);
	}
	else if (v_q->tmp[v_q->i] == '"')
	{
		tmp = ft_quote_str(v_q, '"', var, new);
		*new = ft_strjoinsp2(*new, tmp, 0, v_q);
		if (tmp)
			free(tmp);
	}
}

char	*ft_space_str(t_var *var)
{
	t_var_quote	v_q;
	char		*new;

	var->is_pquote = false;
	if (check_syntax_error(var, 0) == true)
	{
		g_return_value = 2;
		return (NULL);
	}
	var->is_squote = false;
	v_q.tmp = ft_strdup(var->str_in);
	if (!v_q.tmp)
		return (NULL);
	v_q.i = 0;
	v_q.t[1] = 0;
	new = NULL;
	while (v_q.tmp && v_q.i <= (int)ft_strlen(v_q.tmp) && v_q.tmp[v_q.i])
	{
		fill_str(var, &v_q, &new);
		v_q.i++;
	}
	free(v_q.tmp);
	return (new);
}

/*bool	already_pipe(t_token t_new)		//plus besoin
{
	if (token_last(&t_new)->type == PIPE)
		return (true);
	else
		return (false);
}*/
