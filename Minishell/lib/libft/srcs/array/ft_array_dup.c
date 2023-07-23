/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:42:00 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/13 16:42:00 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "memory.h"
#include "str.h"

void	**ft_array_dup(void **array, bool free_array, bool dup_strings)
{
	size_t	array_length;
	size_t	i;
	void	**new_array;

	array_length = ft_array_length(array);
	new_array = ft_calloc(array_length + 1, sizeof(void *));
	if (!new_array)
		return (NULL);
	if (dup_strings)
	{
		i = 0;
		while (i < array_length)
		{
			new_array[i] = ft_strdup(array[i]);
			i++;
		}
	}
	else
		ft_memcpy(new_array, array, array_length * sizeof(void *));
	if (free_array)
		ft_free_array(array);
	return (new_array);
}
