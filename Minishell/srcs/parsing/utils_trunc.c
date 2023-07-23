/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:54:11 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 19:22:11 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*fill_dup(char *str, int start, t_var var, t_var_quote *v_q)
{
	char	*tmp;
	int		j;

	tmp = malloc(sizeof(char) * (v_q->k + 1));
	if (!tmp)
	{
		exit_trunc(&var);
	}
	j = 0;
	while (j < v_q->k)
	{
		if (str[start + j] == '`' && var.is_pquote == true)
			tmp[j] = '|';
		else if (str[start + j] == '~' && var.is_squote == true)
			tmp[j] = ' ';
		else
			tmp[j] = str[start + j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_trunc(char *str, int start, char *c, t_var var)
{
	t_var_quote	v_q;

	v_q.i = start;
	v_q.j = 0;
	v_q.k = 0;
	while (c[v_q.k])
	{
		if (!str || str[v_q.i] == c[v_q.k])
			return (ft_calloc(1, 1));
		v_q.k++;
	}
	v_q.k = 0;
	while (str[v_q.i] && str[v_q.i] != c[v_q.j])
	{
		while (c[v_q.j] && str[v_q.i] != c[v_q.j])
			v_q.j++;
		if (c[v_q.j])
			break ;
		v_q.i++;
		v_q.k++;
		v_q.j = 0;
	}
	v_q.tmp = fill_dup(str, start, var, &v_q);
	return (v_q.tmp);
}

// char	*ft_trunc_char(char *str, int start, char c, t_var var)
// {
// 	char	*s;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = start;
// 	j = 0;
// 	k = 0;
// 	if (!str || str[i] == c)
// 		return ("");
// 	while (str[i] && str[i] != c)
// 	{
// 		i++;
// 		k++;
// 	}
// 	s = fill_dup(str, start, var, k);
// 	return (s);
// }

// char	*ft_trunc_var(t_var var, t_varenv v_e, int start, char *c)
// {
// 	char	*s;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = start;
// 	j = 0;
// 	k = 0;
// 	while (c[k])
// 	{
// 		if (!var.s[v_e.j] || var.s[v_e.j][i] == c[k])
// 			return ("");
// 		k++;
// 	}
// 	k = 0;
// 	while (var.s[v_e.j][i] && var.s[v_e.j][i] != c[j])
// 	{
// 		while (c[j] && var.s[v_e.j][i] != c[j])
// 			j++;
// 		if (c[j])
// 			break ;
// 		i++;
// 		k++;
// 		j = 0;
// 	}
// 	s = fill_dup(var.s[v_e.j], start, var, k);
// 	return (s);
// }
