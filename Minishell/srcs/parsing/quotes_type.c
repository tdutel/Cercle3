/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:46:00 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 18:40:06 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	no_quote_bis(t_var *var, t_var_quote *v_q);

static void	fill_quote(char *str_tmp, t_var *var, t_var_quote *v_q)
{
	if (str_tmp[v_q->i] == '`' && var->is_pquote == true)
		v_q->t[0] = '|';
	else if (str_tmp[v_q->i] == '~' && var->is_squote == true)
		v_q->t[0] = ' ';
	else
		v_q->t[0] = str_tmp[v_q->i];
}

void	dub_quote(char *str_tmp, t_var *var, t_varenv *v_e, char **tmp)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	v_q.i = 1;
	var->env = NULL;
	if (is_env_in_str(str_tmp) == true)
	{
		v_q.tmp = ft_trunc(str_tmp, 1, "$", *var);
		*tmp = ft_strjoinsp(*tmp, v_q.tmp, 0);
		ft_free_secure(&v_q.tmp);
		quote_env(str_tmp, var, v_e);
		var->env = ft_reload_dup(var->env, var);
		*tmp = ft_strjoinsp(*tmp, var->env, 0);
		ft_free_secure(&var->env);
	}
	else
	{
		while (str_tmp[v_q.i] != '"' && str_tmp[v_q.i])
		{
			fill_quote(str_tmp, var, &v_q);
			*tmp = ft_strjoinsp(*tmp, v_q.t, 0);
			v_q.i++;
		}
	}
}

void	single_quote(char *str_tmp, t_var *var, char **tmp)
{
	t_var_quote	v_q;

	v_q.i = 1;
	v_q.t[1] = '\0';
	while (str_tmp[v_q.i] != '\'' && str_tmp[v_q.i])
	{
		fill_quote(str_tmp, var, &v_q);
		*tmp = ft_strjoinsp(*tmp, v_q.t, 0);
		v_q.i++;
	}
}

int	no_quote(t_var *var, t_varenv *v_e, t_var_quote *v_q)
{
	char	*trc_tmp;

	if (has_in_out(v_q->split_tmp, v_q->i) == true)
		return (-1);
	if (is_env_in_str(v_q->split_tmp[v_q->i]) == true)
	{
		trc_tmp = ft_trunc(v_q->split_tmp[v_q->i], 0, "$", *var);
		v_q->tmp = ft_strjoinsp(v_q->tmp, trc_tmp, 0);
		ft_free_secure(&trc_tmp);
		quote_env(v_q->split_tmp[v_q->i], var, v_e);
		var->env = ft_reload_dup(var->env, var);
		v_q->tmp = ft_strjoinsp(v_q->tmp, var->env, 0);
		ft_free_secure(&var->env);
	}
	else
	{
		no_quote_bis(var, v_q);
	}
	return (0);
}

static void	no_quote_bis(t_var *var, t_var_quote *v_q)
{
	v_q->j = 0;
	while (v_q->split_tmp[v_q->i][v_q->j])
	{
		if (v_q->split_tmp[v_q->i][v_q->j] == '`' && var->is_pquote == true)
			v_q->t[0] = '|';
		else if (v_q->split_tmp[v_q->i][v_q->j] == '~'
					&& var->is_squote == true)
			v_q->t[0] = ' ';
		else
			v_q->t[0] = v_q->split_tmp[v_q->i][v_q->j];
		v_q->tmp = ft_strjoinsp(v_q->tmp, v_q->t, 0);
		v_q->j++;
	}
}
