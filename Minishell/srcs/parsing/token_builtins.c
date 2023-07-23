/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:14:25 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 10:27:25 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_arg_builtin(t_var *var, t_varenv *v_e);

void	token_builtin(t_var *var)
{
	t_varenv	v_e;

	var->arg = NULL;
	v_e.j = var->i + 1;
	while (var->s[v_e.j])
	{
		fill_arg_builtin(var, &v_e);
		var->arg = ft_strjoinsp(var->arg, "`", 0);
		v_e.j++;
	}
	var->new_tkn->type = BUILTIN;
	var->new_tkn->content[0] = ft_strdup(var->s[var->i]);
	var->new_tkn->content[1] = ft_strdup(var->arg);
	ft_free_secure(&var->arg);
}

static void	fill_arg_builtin(t_var *var, t_varenv *v_e)
{
	char	*tmp;

	if (is_quote_in(var->s[v_e->j]) == 0)
	{
		if (has_in_out(var->s, v_e->j) == false
			&& is_env_in(*var, v_e->j) == false)
			var->arg = ft_strjoinsp(var->arg, var->s[v_e->j], 0);
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
	else if (is_quote_in(var->s[v_e->j]) != 0
		&& has_in_out(var->s, v_e->j - 1) == false)
	{
		quote_manager(var, v_e);
		var->arg = ft_strjoinsp(var->arg, var->quote, 0);
		ft_free_secure(&var->quote);
	}
}
