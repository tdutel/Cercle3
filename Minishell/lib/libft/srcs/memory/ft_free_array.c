/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:40:09 by gd-harco          #+#    #+#             */
/*   Updated: 2022/12/15 16:40:10 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/array.h"

void	ft_free_array(void **tab)
{
	int	i;
	int	j;

	if (tab)
	{
		j = ft_array_length(tab);
		i = 0;
		while (i < j)
			free(tab[i++]);
		free(tab);
	}
}
