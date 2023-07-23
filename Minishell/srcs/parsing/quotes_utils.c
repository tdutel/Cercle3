/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:39:54 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 18:40:07 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_quote(t_var_quote *v_q)
{
	if (v_q->tmp)
		ft_free_secure(&v_q->tmp);
	if (v_q->split_tmp)
		ft_free_split_secure(&v_q->split_tmp);
}

static void	fill_dup(char *str, t_var *var, t_var_quote *v_q)
{
	if (str[v_q->i] == '`' && var->is_pquote == true)
	{
		v_q->t[0] = '|';
		var->is_pquote = false;
	}
	else if (str[v_q->i] == '~' && var->is_squote == true)
	{
		v_q->t[0] = ' ';
		var->is_squote = false;
	}
	if (str[v_q->i] == '"')
		v_q->t[0] = '\0';
	else
		v_q->t[0] = str[v_q->i];
	v_q->tmp = ft_strjoinsp(v_q->tmp, v_q->t, 0);
}

char	*ft_reload_dup(char *str, t_var *var)
{
	t_var_quote	v_q;

	v_q.i = 0;
	v_q.tmp = NULL;
	v_q.t[1] = '\0';
	while (str[v_q.i])
	{
		fill_dup(str, var, &v_q);
		v_q.i++;
	}
	ft_free_secure(&var->env);
	return (v_q.tmp);
}

static size_t	get_length(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	size_t	y;

	if (start > ft_strlen(s))
		return (0);
	x = start;
	y = 0;
	if (len == 0)
		return (0);
	if (len == start)
		return (len);
	while (s[x] && x < (len + start))
	{
		x++;
		y++;
	}
	return (y);
}

char	*ft_substrvar(char const *s, unsigned int start, size_t len, t_var var)
{
	char	*result;
	size_t	result_length;
	size_t	x;

	if (s == NULL)
		return (NULL);
	result_length = get_length(s, start, len);
	result = malloc(sizeof(char) * (result_length + 1));
	if (result == NULL)
		return (NULL);
	x = 0;
	while (x < result_length)
	{
		if (s[start] == '`' && var.is_pquote == true)
			result[x] = '|';
		else if (s[start] == '~' && var.is_squote == true)
			result[x] = ' ';
		else
			result[x] = s[start];
		x++;
		start++;
	}
	result[x] = '\0';
	return (result);
}
