/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:22:41 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/11 13:55:16 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_env_symbol(t_var *var, char *str_tmp, t_varenv *v_e)
{
	char	*ret_val;

	if (str_tmp[v_e->i + 1 + v_e->k] == '?')
	{
		if (str_tmp[v_e->i + v_e->k] == '$')
		{
			ret_val = ft_itoa(g_return_value);
			var->env = ft_strjoinsp(var->env, ret_val, 0);
			free(ret_val);
		}
		else
			return (0);
	}
	else
		var->env = ft_strjoinsp(var->env, "$", 0);
	if (str_tmp[v_e->i + 1 + v_e->k] == '\0'
		|| str_tmp[v_e->i + 1 + v_e->k + 1] == '\0')
		return (1);
	else
		return (0);
}

int	env_symbol(t_var *var, char *str, t_varenv *v_e)
{
	char	*ret_val;

	if (str[v_e->i + 1 + v_e->k] == '?')
	{
		if (var->s[v_e->j][v_e->i + v_e->k] == '$')
		{
			ret_val = ft_itoa(g_return_value);
			var->env = ft_strjoinsp(var->env, ret_val, 0);
			free(ret_val);
		}
		else
			return (0);
	}
	else
	{
		var->env = ft_strjoinsp(var->env, "$", 0);
	}
	if (str[v_e->i + 1 + v_e->k] == '\0'
		|| str[v_e->i + 1 + v_e->k + 1] == '\0')
		return (1);
	else
		return (0);
}
