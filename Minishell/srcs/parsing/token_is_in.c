/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:17:34 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/15 10:40:11 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_quote(char *str, int j, char c);

bool	is_env_in(t_var var, int j)
{
	int	i;

	i = 0;
	while (var.s[j][i])
	{
		if (var.s[j][i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	is_env_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

int	is_quote_in(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		else if (str[i] == '"')
			return (2);
		i++;
	}
	return (0);
}

int	is_quote_between(char *str, int i)
{
	int	j;

	j = i;
	if (i == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			return (find_quote(str, j, '\''));
		}
		else if (str[i] == '"')
		{
			return (find_quote(str, j, '"'));
		}
		else
		{
			i++;
			j = i;
		}
	}
	return (0);
}

static int	find_quote(char *str, int j, char c)
{
	while (j >= 0)
	{
		if (str[j--] == c)
			return (1);
	}
	return (0);
}
