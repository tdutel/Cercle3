/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:21:41 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/21 13:22:07 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	ft_sort_array(char **array_to_sort)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (array_to_sort[i])
	{
		j = i + 1;
		while (array_to_sort[j])
		{
			if (ft_strcmp(array_to_sort[i], array_to_sort[j]) > 0)
			{
				temp = array_to_sort[i];
				array_to_sort[i] = array_to_sort[j];
				array_to_sort[j] = temp;
			}
			j++;
		}
		i++;
	}
}
