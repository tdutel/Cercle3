/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_array_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:21:17 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/21 13:21:21 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "memory.h"
/**
 * @brief Create a duplicate of an array with an additional pointer at the end.
 * @param array The array in which to add the pointer.
 * @param content The pointer to add.\n
 * It must have been allocated with malloc(3) to avoid causing issue
 * when the array will be freed later in the program.
 * @return The new array with the pointer added.
 */
void	**ft_add_array_line(void **array, void *content)
{
	void	**new_array;

	new_array = ft_calloc(ft_array_length(array) + 2, sizeof(void *));
	if (!new_array)
		return (NULL);
	ft_memmove(new_array, array, ft_array_length(array) * sizeof(void *));
	new_array[ft_array_length(array)] = content;
	free(array);
	return (new_array);
}
