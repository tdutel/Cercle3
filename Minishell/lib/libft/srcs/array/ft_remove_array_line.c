/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_array_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:21:25 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/21 13:21:29 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <stdbool.h>

/**
 * @brief Remove a line from an array.
 * @param array The array from which to remove the line.
 * @param index The index of the line to remove.
 * @param free_line Whether to free the line or not.
 */
void	ft_remove_array_line(void **array, size_t index, bool free_line)
{
	size_t	i;

	i = index;
	if (free_line)
		free(array[index]);
	while (array[i + 1])
	{
		array[i] = array[i + 1];
		i++;
	}
	array[i] = NULL;
}
