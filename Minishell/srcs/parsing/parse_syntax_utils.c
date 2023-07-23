/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:56:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 16:35:56 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	in_out_in(t_var var, int i)
{
	int	j;

	j = 0;
	while (var.s[i][j])
	{
		if (var.s[i][j] == '<' || var.s[i][j] == '>')
			return (true);
		j++;
	}
	return (false);
}

char	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	return (str[i]);
}

bool	out2_check(t_var *var, int i)
{
	if (((var->str_in[i] == '>' && var->str_in[i + 1] == '>')
			&& (var->str_in[i + 2] == '>' && (var->str_in[i + 3] == '>')))
		|| ((var->str_in[i] == '<' && var->str_in[i + 1] == '<')
			&& (var->str_in[i + 2] == '>' && var->str_in[i + 3] == '>')))
	{
		ft_putendl_fd(OUT2_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	io_check(t_var *var, int i)
{
	if ((var->str_in[i] == '>' && var->str_in[i + 1] == '<')
		&& (var->str_in[i + 2] == '>'))
	{
		ft_putendl_fd(IO_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}
