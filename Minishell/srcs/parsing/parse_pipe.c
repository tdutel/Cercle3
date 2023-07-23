/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:11:18 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 16:33:40 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	pipe_parse(char *str);

bool	pipe_check(char *str)
{
	int	i;

	if (str[0] == '|' && str[1] != '|')
		return (ft_putendl_fd(PIPE_SYNTAX_ERR, STDERR_FILENO), true);
	else if (str[0] == '|' && str[1] == '|')
		return (ft_putendl_fd(PIPE2_SYNTAX_ERR, STDERR_FILENO), true);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '|' && str[i + 1] == '|' && str[i + 2] != '|'
				&& is_quote_between(str, i) == 0)
			|| (str[i] == '|' && str[i + 1] == '\0'))
			return (ft_putendl_fd(PIPE_SYNTAX_ERR, STDERR_FILENO), true);
		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|'
			&& is_quote_between(str, i) == 0)
			return (ft_putendl_fd(PIPE2_SYNTAX_ERR, STDERR_FILENO), true);
		i++;
	}
	if (pipe_parse(str) == true)
		return (true);
	return (false);
}

static bool	is_pipe_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

static bool	pipe_parse(char *str)
{
	int		i;
	char	**s;

	i = 0;
	s = ft_split(str, ' ');
	while (s[i] && is_pipe_in(s[i]) == false)
		i++;
	if (!s[i] || !s[i + 1])
		return (ft_free_split(s), false);
	if (last_char(s[i]) == '|')
	{
		if (s[i + 1][0] == '|' && s[i + 1][1] != '|')
		{
			ft_putendl_fd(PIPE_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(s), true);
		}
		else if (s[i + 1][0] == '|' && s[i + 1][1] == '|')
		{
			ft_putendl_fd(PIPE2_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(s), true);
		}
	}
	ft_free_split(s);
	return (false);
}
