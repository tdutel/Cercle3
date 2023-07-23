/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:12:47 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/12 13:55:21 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		add_quote_env(char *str_tmp, t_var *var, t_varenv *v_e, int l);
static void		find_quote_env(char *str_tmp, t_varenv *v_e, int l);
static int		fill_quote_env(char *str_tmp, t_var *var, t_varenv *v_e);
static void		fill_quote_env_bis(char *str_tmp, t_var *var, t_varenv *v_e);
/*
	la variable l va permettre de faire une comparaison dans la chaine,
	pour savoir combien de var d'env ont été check et pour toutes les gérer.
*/

void	quote_env(char *str_tmp, t_var *var, t_varenv *v_e)
{
	int	l;

	var->env = NULL;
	v_e->o = 0;
	l = 0;
	while (add_quote_env(str_tmp, var, v_e, l) == 0)
	{
		l++;
	}
}

/*
	add_env_arg permet de remplir var->env de toutes
	les variable d'env et d'autres metachar.
	On return 0 si l'indice de fin est toujours un $
	car cela s'ignifie qu'il reste des var d'env à join.
*/

static int	add_quote_env(char *str_tmp, t_var *var, t_varenv *v_e, int l)
{
	int		ret_value;
	char	*tmp;

	v_e->i = -1 + v_e->o;
	v_e->k = 0;
	v_e->m = 0;
	while (v_e->m <= l)
	{
		find_quote_env(str_tmp, v_e, l);
	}
	ret_value = fill_quote_env(str_tmp, var, v_e);
	if (ret_value == 1)
		return (ret_value);
	tmp = ft_trunc(str_tmp, v_e->i + 1 + v_e->k, "$", *var);
	if (str_tmp && str_tmp[v_e->i + 1 + v_e->k + ft_strlen
			(tmp)] == '$')
		return (ft_free_secure(&tmp), 0);
	else
		return (ft_free_secure(&tmp), 1);
}

/*
	find_env_var permet de parcourir la chaine jusqu'à trouver le $
	i est ainsi l'indice du $. On parcourt ensuite la suite avec k
	k est ainsi le nombre de charactere de la variable d'env $.
	On regarde si m = l pour voir si on a déjà traité cette variable
	d'environnement $. Sinon, on remet k à 0 et on implémente m.
*/
static void	find_quote_env(char *str_tmp, t_varenv *v_e, int l)
{
	v_e->i++;
	while (str_tmp
		&& str_tmp[v_e->i] && str_tmp[v_e->i] != '$')
		v_e->i++;
	while (str_tmp && str_tmp[v_e->i + 1 + v_e->k]
		&& !is_metachar(str_tmp[v_e->i + 1 + v_e->k]))
		v_e->k++;
	if (v_e->m != l)
	{
		v_e->i = v_e->i + v_e->k;
		v_e->k = 0;
	}
	v_e->m++;
}

/*
	fill_env_var permet de remplir la variable var_env avec la variable
	d'environnement associée via ft_strjoin() ft_substr() et en cherchant
	la ligne d'envp correspondant via ft_strnstr. le return permet de gérer
	le cas d'un simple $ dans add_env_arg()
	et ansi de sortir de la boucle dans env_arg()
*/

static int	fill_quote_env(char *str_tmp, t_var *var, t_varenv *v_e)
{
	v_e->var_env = ft_substrvar(str_tmp, v_e->i + 1, v_e->k, *var);
	if (str_tmp && str_tmp[v_e->i + 1 + v_e->k] == '?')
	{
		quote_env_symbol(var, str_tmp, v_e);
		v_e->k++;
	}
	else if (v_e->var_env && (v_e->var_env[0] == '\0'))
		quote_env_symbol(var, str_tmp, v_e);
	v_e->m = 0;
	while (var->env_cpy[v_e->m] && v_e->var_env && ft_strnstr
		(var->env_cpy[v_e->m], v_e->var_env, ft_strlen(v_e->var_env)) == NULL)
		v_e->m++;
	fill_quote_env_bis(str_tmp, var, v_e);
	return (2);
}

static void	fill_quote_env_bis(char *str_tmp, t_var *var, t_varenv *v_e)
{
	char	*sub_tmp;
	char	*trc_tmp;

	if (var->env_cpy && var->env_cpy[v_e->m]
		&& var->env_cpy[v_e->m][ft_strlen(v_e->var_env)] == '=')
	{
		sub_tmp = ft_substrvar(var->env_cpy[v_e->m], v_e
				->k + 1, ft_strlen(var->env_cpy[v_e->m]) - v_e->k, *var);
		var->env = ft_strjoinsp(var->env, sub_tmp, 0);
		ft_free_secure(&sub_tmp);
	}
	if (str_tmp && str_tmp[v_e->i + 1 + v_e->k] != '$')
	{
		trc_tmp = ft_trunc(str_tmp, v_e->i + 1 + v_e->k, "$", *var);
		sub_tmp = ft_substrvar(str_tmp, v_e->i + 1 + v_e->k,
				ft_strlen(trc_tmp), *var);
		var->env = ft_strjoinsp(var->env, sub_tmp, 0);
		ft_free_secure(&trc_tmp);
		ft_free_secure(&sub_tmp);
	}
	ft_free_secure(&v_e->var_env);
}
