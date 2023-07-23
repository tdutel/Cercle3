/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:55:32 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:03:16 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (check_for_equal(envp[i]))
			ft_dprintf(STDOUT_FILENO, "%s\n", envp[i]);
		i++;
	}
	g_return_value = 0;
}
