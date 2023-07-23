/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:56:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 16:35:42 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	newline_check(t_var *var, int i)
{
	if ((var->str_in[i] == '<'
			&& ((var->str_in[i + 1] == '\0')
				|| (var->str_in[i + 1] == '<' && var->str_in[i + 2] == '\0')
				|| (var->str_in[i + 1] == '>' && var->str_in[i + 2] == '\0')
				|| (var->str_in[i + 1] == '<' && var->str_in[i + 2] == '<'
					&& var->str_in[i + 3] == '\0')
			))
		|| (var->str_in[i] == '>'
			&& ((var->str_in[i + 1] == '\0')
				|| (var->str_in[i + 1] == '>' && var->str_in[i + 2] == '\0')
			)))
	{
		ft_putendl_fd(NL_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	in_check(t_var *var, int i)
{
	if ((var->str_in[i] == '>'
			&& (var->str_in[i + 1] == '<' && var->str_in[i + 2] == '\0'))
		|| (var->str_in[i] == '<' && var->str_in[i + 1] == '<'
			&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<'
			&& (var->str_in[i + 4] == '\0')))
	{
		ft_putendl_fd(IN_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	in2_check(t_var *var, int i)
{
	if ((var->str_in[i] == '>' && var->str_in[i + 1] == '>'
			&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<')
		|| (var->str_in[i] == '<' && var->str_in[i + 1] == '<'
			&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<'
			&& var->str_in[i + 4] == '<' && var->str_in[i + 5] != '<'))
	{
		ft_putendl_fd(IN2_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	in3_check(t_var *var, int i)
{
	if (var->str_in[i] == '<' && var->str_in[i + 1] == '<'
		&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<'
		&& var->str_in[i + 4] == '<' && var->str_in[i + 5] == '<')
	{
		ft_putendl_fd(IN3_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	out_check(t_var *var, int i)
{
	if ((var->str_in[i] == '<' && var->str_in[i + 1] == '<')
		&& (var->str_in[i + 2] == '>' && (var->str_in[i + 3] == '\0')))
	{
		ft_putendl_fd(OUT_SYNTAX_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);
}
