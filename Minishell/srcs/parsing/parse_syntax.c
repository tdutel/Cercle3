/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:35 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 16:07:37 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_parse(t_var var);
static bool	check_parse_bis(t_var var, int i);

bool	check_syntax_error(t_var *var, int i)
{
	if (!var->str_in)
		return (false);
	if (pipe_check(var->str_in) == true)
		return (true);
	while (var->str_in[i] && is_quote_between(var->str_in, i) == 0)
	{
		if (newline_check(var, i) == true)
			return (true);
		else if (in_check(var, i) == true)
			return (true);
		else if (in2_check(var, i) == true)
			return (true);
		else if (in3_check(var, i) == true)
			return (true);
		else if (out_check(var, i) == true)
			return (true);
		else if (out2_check(var, i) == true)
			return (true);
		else if (io_check(var, i) == true)
			return (true);
		if (check_parse(*var) == true)
			return (true);
		i++;
	}
	return (false);
}

static bool	check_parse(t_var var)
{
	int		i;

	i = 0;
	var.s = ft_split(var.str_in, ' ');
	while (var.s[i] && in_out_in(var, i) == false)
		i++;
	if (!var.s[i] || !var.s[i + 1])
		return (ft_free_split(var.s), false);
	if (last_char(var.s[i]) == '<' || last_char(var.s[i]) == '>')
	{
		if (var.s[i + 1][0] == '>' && var.s[i + 1][1] != '>')
		{
			ft_putendl_fd(OUT_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(var.s), true);
		}
		else if (var.s[i + 1][0] == '>' && var.s[i + 1][1] == '>')
		{
			ft_putendl_fd(OUT2_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(var.s), true);
		}
		if (check_parse_bis(var, i) == true)
			return (true);
	}
	ft_free_split(var.s);
	return (false);
}

static bool	check_parse_bis(t_var var, int i)
{
	if (var.s[i + 1][0] == '<' && var.s[i + 1][1] == '<'
		&& var.s[i + 1][2] == '<')
	{
		ft_putendl_fd(IN3_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	else if (var.s[i + 1][0] == '<' && var.s[i + 1][1] == '<')
	{
		ft_putendl_fd(IN2_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	else if (var.s[i + 1][0] == '<' && var.s[i + 1][1] == '>')
	{
		ft_putendl_fd(IO_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	else if (var.s[i + 1][0] == '<')
	{
		ft_putendl_fd(IN_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	return (false);
}
