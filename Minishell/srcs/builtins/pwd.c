/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:02:31 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 11:10:01 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str == NULL)
	{
		ft_dprintf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
		g_return_value = 1;
	}
	else
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", str);
		g_return_value = 0;
	}
	free(str);
}
