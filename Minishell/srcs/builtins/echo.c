/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:31:54 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:27:22 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_n(char **argv, int *i, int *j, bool *n);

void	echo(char **argv)
{
	int		i;
	int		j;
	bool	n;

	i = 1;
	n = false;
	while (argv[i] && argv[i][0] == '-')
	{
		if (handle_n(argv, &i, &j, &n) == false)
			break ;
	}
	while (argv[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", argv[i]);
		if (argv[i + 1])
			ft_dprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (!n)
		ft_dprintf(STDOUT_FILENO, "\n");
	g_return_value = 0;
}

bool	handle_n(char **argv, int *i, int *j, bool *n)
{
	if (argv[*i][1] == 'n')
	{
		*j = 2;
		while (argv[*i][*j] == 'n')
			(*j)++;
		if (argv[*i][*j] == '\0')
		{
			*n = true;
			(*i)++;
			return (true);
		}
		else
			return (false);
	}
	else
		return (false);
}
