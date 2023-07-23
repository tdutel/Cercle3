/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_add_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:42:00 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/13 16:42:00 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "memory.h"

/**
 * @function ft_merge_array
 * @brief Merge two arrays of strings into one, allocated with malloc(3). \n
 * If one of the arrays is NULL,
 * NULL is returned and nothing is freed. \n
 * The two arrays must be NULL terminated.
 * User must specify if he wants to free both array.
 * @param p_array The first array to be merged.
 * @param s_array The second array to be merged.
 * @param free_array If true, free the first array
 * (only the array, not the strings inside)
 * @param free_line If true, free the second array
 * (only the array, not the strings inside)
 * @return The newly allocated array,
 * or NULL if an allocation failed/one of the input is NULL.
 * @author gd-harco
 */
char	**ft_merge_array(char **p_array, char **s_array,
				bool free_array, bool free_line)
{
	char	**new_array;
	size_t	old_length;
	size_t	new_length;

	if (!p_array || !s_array)
		return (NULL);
	old_length = ft_array_length((void **)p_array);
	new_length = old_length + ft_array_length((void **)s_array);
	new_array = ft_calloc(new_length + 1,
			sizeof(char *));
	if (!new_array)
		return (NULL);
	ft_memmove(new_array, p_array, old_length * sizeof(char *));
	ft_memmove(new_array + old_length, s_array, new_length * sizeof(char *));
	if (free_array)
		free(p_array);
	if (free_line)
		free(s_array);
	return (new_array);
}
