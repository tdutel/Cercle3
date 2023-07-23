/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:25:29 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 10:29:42 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_trunc_start(char *str, char *c, t_var var);
static void	init_quote_manager(t_var *var, t_varenv *v_e, t_var_quote *v_q);

void	quote_manager(t_var *var, t_varenv *v_e)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	var->quote = NULL;
	v_q.split_tmp = ft_split(var->s[v_e->j], '\\');
	if (!v_q.split_tmp)
		return ;
	v_q.tmp = NULL;
	var->quote = NULL;
	v_q.i = 0;
	while (v_q.split_tmp[v_q.i])
	{
		if (is_quote_in(v_q.split_tmp[v_q.i]) == 1)
			single_quote(v_q.split_tmp[v_q.i], var, &v_q.tmp);
		else if (is_quote_in(v_q.split_tmp[v_q.i]) == 2)
			dub_quote(v_q.split_tmp[v_q.i], var, v_e, &v_q.tmp);
		else
		{
			if (no_quote(var, v_e, &v_q) == -1)
				return (free_quote(&v_q));
		}
		v_q.i++;
	}
	var->quote = ft_strdup(v_q.tmp);
	free_quote(&v_q);
}

void	quote_manager_inout(t_var *var, t_varenv *v_e)
{
	t_var_quote	v_q;

	init_quote_manager(var, v_e, &v_q);
	while (v_q.split_tmp[v_q.i])
	{
		if (is_quote_in(v_q.split_tmp[v_q.i]) == 1)
			single_quote(v_q.split_tmp[v_q.i], var, &v_q.tmp);
		else if (is_quote_in(v_q.split_tmp[v_q.i]) == 2)
			dub_quote(v_q.split_tmp[v_q.i], var, v_e, &v_q.tmp);
		else
		{
			if (no_quote(var, v_e, &v_q) == -1)
				return (free_quote(&v_q));
		}
		v_q.i++;
	}
	var->quote = ft_strdup(v_q.tmp);
	free_quote(&v_q);
}

static void	init_quote_manager(t_var *var, t_varenv *v_e, t_var_quote *v_q)
{
	char		*trc_tmp;

	v_q->t[1] = '\0';
	var->quote = NULL;
	trc_tmp = ft_trunc_start(var->s[v_e->j], "<>", *var);
	v_q->split_tmp = ft_split(trc_tmp, '\\');
	if (!v_q->split_tmp)
		return ;
	free(trc_tmp);
	v_q->tmp = NULL;
	var->quote = NULL;
	v_q->i = 0;
}

static char	*ft_trunc_start(char *str, char *c, t_var var)
{
	t_var_quote	v_q;

	v_q.i = 0;
	v_q.j = 0;
	while (str[v_q.i])
	{
		while (c[v_q.j])
		{
			if (str[v_q.i] == c[v_q.j])
				break ;
			v_q.j++;
		}
		if (str[v_q.i] != c[v_q.j])
			break ;
		v_q.i++;
		v_q.j = 0;
	}
	return (ft_substrvar(str, v_q.i, ft_strlen(str) - v_q.i, var));
}

/*

/!\
gerer "$ , $USER" et $,$USER pour afficher la , est non $tdutel

gerer les quote dans infile outfile : ls > "<E" doit creer un file <E


echo "$(echo "upg")"	=	echo $(echo "upg")
		upg

echo '$(echo"upg")'
	$(echo"upg")

*/
