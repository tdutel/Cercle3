/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:11:56 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 10:27:12 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	token_quotes_check(t_var *var, t_varenv v_e);
static void	fill_arg_cmd(t_var *var, t_varenv *v_e);

void	token_cmd(t_var *var)
{
	t_varenv	v_e;

	v_e.j = var->i;
	var->arg = NULL;
	token_quotes_check(var, v_e);
	v_e.j++;
	while (var->s[v_e.j])
	{
		fill_arg_cmd(var, &v_e);
		var->arg = ft_strjoinsp(var->arg, "`", 0);
		v_e.j++;
	}
	var->new_tkn->type = CMD;
	var->new_tkn->content[0] = check_var(var, &v_e);
	var->new_tkn->content[1] = ft_strdup(var->arg);
	ft_free_secure(&var->s_p);
	ft_free_secure(&var->arg);
}

static void	token_quotes_check(t_var *var, t_varenv v_e)
{
	if (is_quote_in(var->s[v_e.j]) == 0)
	{
		var->path = get_path(var->env_cpy);
		var->s_p = process(var->spipe[var->index], var->path, var->i, var);
	}
	else
	{
		quote_manager(var, &v_e);
		var->quote_cmd = true;
		var->s_p = ft_strdup(var->quote);
		ft_free_secure(&var->quote);
	}
}

static void	no_quote_arg(t_var *var, t_varenv *v_e)
{
	char	*tmp;

	if (has_in_out(var->s, v_e->j) == false
		&& is_env_in(*var, v_e->j) == false)
	{
		var->arg = ft_strjoinsp(var->arg, var->s[v_e->j], 0);
	}
	else if (is_env_in(*var, v_e->j) == true
		&& has_in_out(var->s, v_e->j) == false)
	{
		tmp = ft_trunc(var->s[v_e->j], 0, "$", *var);
		var->arg = ft_strjoinsp(var->arg, tmp, 1);
		ft_free_secure(&tmp);
		env_arg(var, v_e);
		var->arg = ft_strjoinsp(var->arg, var->env, 0);
		ft_free_secure(&var->env);
	}
}

static void	fill_arg_cmd(t_var *var, t_varenv *v_e)
{
	if (is_quote_in(var->s[v_e->j]) == 0)
	{
		no_quote_arg(var, v_e);
	}
	else if (is_quote_in(var->s[v_e->j]) != 0
		&& has_in_out(var->s, v_e->j - 1) == false)
	{
		quote_manager(var, v_e);
		var->arg = ft_strjoinsp(var->arg, var->quote, 0);
		ft_free_secure(&var->quote);
	}
}
